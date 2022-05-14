# 第1章 重构，第一个示例

[[toc]]

## 起点

开篇以例子来说明重构的过程

```json
// plays.json
{
  "hamlet": {"name": "Hamlet", "type": "tragedy"},
  "as-like": {"name": "As You Like It", "type": "comedy"},
  "othello": {"name": "Othello", "type": "tragedy"}
}

// invoices.json
{
  {
  	"customer": "BigCo",
  	"performances": [{
  		"playID": "hamlet",
  		"audience": 55
		}, {
  		"playID": "as-like",
  		"audience": 35
		}, {
  		"playID": "othello",
  		"audience": 40
		}]
	}
}
```

```js
function statement(invoice, plays) {
	let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${invoice.customer}\n`;
  const format = new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', minimumFractionDigits: 2}).format;
  for (let perf of invoice.performances) {
    const play = plays[perf.playID];
    let thisAmount = 0;
    
    switch (play.type) {
      case 'tragedy':
        thisAmount = 40000;
        if (perf.audience > 30) {
          thisAmount += 1000 * (perf.audience - 30);
        }
        break;
      case 'comedy':
        thisAmount = 30000;
        if (perf.audience > 20) {
          thisAmount += 10000 + 500 * (perf.audience - 20);
        }
        thisAmount += 300 * perf.audience;
        break;
      default:
        throw new Error(`unknown type: ${play.type}`);
    }
    
    // add volume credits
    volumeCredits += Math.max(perf.audience - 30, 0);
    // add extra credit for every ten comedy attendees
    if ('comedy' === play.type) volumeCredits += Math.floor(perf.audience / 5);
    // print line for this order
    result += `	${play.name}: ${format(thisAmount/100) (${perf.audience} seats)\n}`;
    totalAmount += thisAmount;
  }
  result += `Amount owed is ${format(totalAmount/100)}\n}`
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}

// 输出结果
// Statement for BigCo
//	 Halmet: $650.00 (55 seats)
//	 As You Like It: $580.00 (35 seats)
//	 Othello: $500.00 (40 seats)
// Amount owed is $1,730.00
// You earned 47 credits
```

以上代码组织不清晰。当用户希望对系统做几个修改时，可以通过代码复制来处理，但会留下各种隐患。如果一处发生变化，就有可能需要同时修改多个地方，来保证逻辑相同。随着各种规则变得越来越复杂，适当的修改点将越来越难找，不犯错的机会也越来越少。

需求的变化使重构变得必要。

## 重构的第一步

每当要进行重构时，第一个步骤永远是确保即将修改的代码拥有一组可靠的测试。测试过程需要注重对结果的报告方式。否则就得耗费大把时间来回比对，这会降低开发速度。

## 分解statement函数

⚠️整个重构过程，每一步都应该是经过编译、测试、提交的完整过程(TDD)，都要编写对应的测试用例，这样是为了减少后期排查错误的困扰。

### 提炼函数

现在开始对上栗做重构。可以将statement中的switch语句分解出来，命名为amountFor(..)，形成一个独立的函数。将一块代码抽取成一个函数，遵循一个标准的流程，并命名为**提炼函数(106)**，方便后面可以引用。

```js
function amountFor(perf, play) {
  let thisAmount = 0;
  switch (play.type) {
    case 'tragedy':
      thisAmount = 40000;
      if (perf.audience > 30) {
        thisAmount += 1000 * (perf.audience - 30);
      }
      break;
    case 'comedy':
      thisAmount = 30000;
      if (perf.audience > 20) {
        thisAmount += 10000 + 500 * (perf.audience - 20);
      }
      thisAmount += 300 * perf.audience;
      break;
    default:
      throw new Error(`unknown type: ${play.type}`);
  }
  return thisAmount;
}

// statement 主函数 中对以上函数做引用
function statement(...) {
  // ...
  let thisAmount = amountFor(perf, play);
  // ...
}
```

这里还是要强调，**无论每次重构有多么简单，养成重构即运行测试的习惯是非常重要的**。做完一次修改就运行测试，这样只需要考虑一个很小的改动范围，使得查错与修复问题易如反掌。重构过程的精髓所在：**小步修改，每次修改后就运行测试**。这是防止混乱的关键。

### 变量修改

经过**提炼函数(106)**手法后，可以继续看函数是否还有进一步提升表达能力，**第一个推荐的方式是变量修改**，使变量名更简洁，比如将thisAmount重命名为result。

```js
function amountFor(perf, play) {
  let result = 0;
  switch (play.type) {
    case 'tragedy':
      result = 40000;
      if (perf.audience > 30) {
        result += 1000 * (perf.audience - 30);
      }
      break;
    case 'comedy':
      result = 30000;
      if (perf.audience > 20) {
        result += 10000 + 500 * (perf.audience - 20);
      }
      result += 300 * perf.audience;
      break;
    default:
      throw new Error(`unknown type: ${play.type}`);
  }
  return result;
}
```

作者编码风格：永远将函数的返回值命名为"result"。可以一眼看出它的作用。

### 变量命名

变量命名是代码清晰的关键。在参数取名时，都会默认带上类型名。一般会使用不定冠词修饰它，除非命名另有解释其角色的相关信息。暂时这里先不做处理，先移除不必要的参数变量

### 移除play变量

当分解一个长函数时，可以将play这样的变量移除掉，因为该变量是由performance变量计算得到的，其实没有必要作为参数传入，可以在amountFor函数中重新计算得到。这些不必要的变量会创建很多对应的具有局部作用域的临时变量，会使提炼函数变得更加复杂。这也是重构手法中的**以查询取代临时变量(178)**。

```js
// 提炼出play获取函数
function playFor(aperformance) {
	return plays[aperformance.playID];
}

// statement主函数中引用
function statement(...) {
  // ...
  const play = playFor(perf);
  let thisAmount = amountFor(perf, play);
  // ...
}
```

### 内联变量

使用**内联变量(123)**内联play变量。

```js
function statement(invoice, plays) {
	let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${invoice.customer}\n`;
  const format = new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', minimumFractionDigits: 2}).format;
  for (let perf of invoice.performances) {
  	let thisAmount = amountFor(perf, playFor(perf));
    
    // add volume credits
    volumeCredits += Math.max(perf.audience - 30, 0);
    // add extra credit for every ten comedy attendees
    if ('comedy' === playFor(perf).type) volumeCredits += Math.floor(perf.audience / 5);
    // print line for this order
    result += `	${playFor(perf).name}: ${format(thisAmount/100) (${perf.audience} seats)\n}`;
    totalAmount += thisAmount;
  }
  result += `Amount owed is ${format(totalAmount/100)}\n}`
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}
```

### 改变函数声明

可以直接对amountFor函数修改，**改变函数声明(124)**，移除play参数，也就是将palyFor也内联到amountFor函数中。

```js
function amountFor(perf) {
  let result = 0;
  switch (playFor(perf).type) {
    case 'tragedy':
      result = 40000;
      if (perf.audience > 30) {
        result += 1000 * (perf.audience - 30);
      }
      break;
    case 'comedy':
      result = 30000;
      if (perf.audience > 20) {
        result += 10000 + 500 * (perf.audience - 20);
      }
      result += 300 * perf.audience;
      break;
    default:
      throw new Error(`unknown type: ${playFor(perf).type}`);
  }
  return result;
}

function statement(invoice, plays) {
	let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${invoice.customer}\n`;
  const format = new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', minimumFractionDigits: 2}).format;
  for (let perf of invoice.performances) {
  	let thisAmount = amountFor(perf);
    
    // add volume credits
    volumeCredits += Math.max(perf.audience - 30, 0);
    // add extra credit for every ten comedy attendees
    if ('comedy' === playFor(perf).type) volumeCredits += Math.floor(perf.audience / 5);
    // print line for this order
    result += `	${playFor(perf).name}: ${format(thisAmount/100) (${perf.audience} seats)\n}`;
    totalAmount += thisAmount;
  }
  result += `Amount owed is ${format(totalAmount/100)}\n}`
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}
```

⚠️这里需要注意的是，重构前查找play变量的代码在每次循环中只执行1次，而重构后却执行了3次。**这里需要权衡重构与性能之间的关系**。作者认为这次改动并不太可能对性能有严重影响，**即便真的有所影响，后续再对一段结构良好的代码进行性能调优，也容易得多**。

**作者实际上倡导，在做任何提炼前，先移除局部变量。**

再次基础上，statement又可以继续内联变量thisAmount

```js
function statement(invoice, plays) {
	let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${invoice.customer}\n`;
  const format = new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', minimumFractionDigits: 2}).format;
  for (let perf of invoice.performances) {
    // add volume credits
    volumeCredits += Math.max(perf.audience - 30, 0);
    // add extra credit for every ten comedy attendees
    if ('comedy' === playFor(perf).type) volumeCredits += Math.floor(perf.audience / 5);
    // print line for this order
    result += `	${playFor(perf).name}: ${format(amountFor(perf)/100) (${perf.audience} seats)\n}`;
    totalAmount += amountFor(perf);
  }
  result += `Amount owed is ${format(totalAmount/100)}\n}`
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}
```

重构到这，慢慢能够感受到移除局部变量的好处，逐步的提炼使得整个计算逻辑变得简单了。因此可以继续提炼剩下的两个局部变量，先提炼volumeCredits同时更名：

```js
function volumeCreditsFor(perf) {
  let result = 0; // 原函数中的volumeCredits
  result += Math.max(perf.audience - 30, 0);
  if ('comedy' === playFor(perf).type) result += Math.floor(perf.audience / 5);
  return result;
}

// statement主函数
function statement(...) {
  // ...
  volumeCredits += volumeCreditsFor(perf);
  // ...
}
```

### 移除format变量

临时变量越多，就意味着函数的长度越长，复杂度越高，因此移除临时变量可以很快的精简代码并增加可读性。此时可以继续提炼format：

```js
function usd(aNumber) {
  return new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', minimumFractionDigits: 2}).format(aNumber/100);
}

function statement(invoice, plays) {
	let totalAmount = 0;
  let volumeCredits = 0;
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    volumeCredits += volumeCreditsFor(perf);

    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
    totalAmount += amountFor(perf);
  }
  result += `Amount owed is ${usd(totalAmount)}\n}`
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}
```

⚠️尽管将函数变量改变成函数声明也是一种重构方法，但作者并没有为此手法命名，也未将它纳入重构名录中。

上面的代码中给format函数命名为usd，命名是很具有考究的。要使命名够简短并且还能很清晰地描述其作用。

### 移除volumeCredits、totalAmount局部变量

该变量是通过累加获得的，而for循环中又有别的无关处理，这里采用**拆分循环(227)**将volumeCredits的累加过程独立出来

```js
function statement(invoice, plays) {
	let totalAmount = 0;
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
    totalAmount += amountFor(perf);
  }
  let volumeCredits = 0;
  for (let perf of invoice.performances) {
    volumeCredits += volumeCreditsFor(perf);
  }
  result += `Amount owed is ${usd(totalAmount)}\n}`
  result += `You earned ${volumeCredits} credits\n`;
  return result;
}
```

接着提炼函数，替换变量名并内联：

```js
function totalVolumeCredits() {
  let result = 0; // volumeCredits
  for (let perf of invoice.performances) {
    result += volumeCreditsFor(perf);
  }
  return result;
}

function statement(invoice, plays) {
	let totalAmount = 0;
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
    totalAmount += amountFor(perf);
  }
  result += `Amount owed is ${usd(totalAmount)}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;
}
```

⚠️这里可能会有很多开发人员有疑问，增加重复的循环难道不会给性能上带来困扰吗？其实我自己也怀疑，但后面作者做了阐述。"大多数时候，重复一次这样的循环对性能的影响都可忽略不计。如果在重构前后进行计时，很可能甚至都注意不到运行速度的变化。但**还是有可能会存在重构使得性能受到影响，做法是先不管它，继续重构，有了一份结构良好的代码，回头调优其性能也容易得多**。"因此，在重构过程的性能问题，作者的建议是：**大多数情况下可以忽略它。如果重构引入了性能损耗，先完成重构，再做性能优化。**

接着继续移除totalAmount：

```js
function totalAmount() {
  let result = 0; // totalAmount
	for (let perf of invoice.performances) {
    result += amountFor(perf);
  }
  return result;
}

function statement(invoice, plays) {
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(totalAmount())}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;
}
```

## 目前的重构结果

现在，可以先大致浏览下重构后的代码全貌了：

```js
function statement(invoice, plays) {
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(totalAmount())}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;

  function totalAmount() {
    let result = 0; // totalAmount
    for (let perf of invoice.performances) {
      result += amountFor(perf);
    }
    return result;
  }
  
  function totalVolumeCredits() {
    let result = 0; // volumeCredits
    for (let perf of invoice.performances) {
      result += volumeCreditsFor(perf);
    }
    return result;
  }
  
  function usd(aNumber) {
    return new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD', minimumFractionDigits: 2}).format(aNumber/100);
  }

	function volumeCreditsFor(perf) {
    let result = 0; // 原函数中的volumeCredits
    result += Math.max(perf.audience - 30, 0);
    if ('comedy' === playFor(perf).type) result += Math.floor(perf.audience / 5);
    return result;
  }
  
  function playFor(aperformance) {
    return plays[aperformance.playID];
  }
  
  function amountFor(perf) {
    let result = 0;
    switch (playFor(perf).type) {
      case 'tragedy':
        result = 40000;
        if (perf.audience > 30) {
          result += 1000 * (perf.audience - 30);
        }
        break;
      case 'comedy':
        result = 30000;
        if (perf.audience > 20) {
          result += 10000 + 500 * (perf.audience - 20);
        }
        result += 300 * perf.audience;
        break;
      default:
        throw new Error(`unknown type: ${playFor(perf).type}`);
    }
    return result;
	}
}
```

## 进一步重构，拆分计算阶段与格式化阶段

经过上面的重构，只是为原函数添加足够的结构，以便能更好地理解，看清它的逻辑结构。这也只是重构早期的一个步骤。

接下来就是**拆分阶段(154)**，将逻辑分成两部分：一部分计算详单所需的数据，另一部分将数据渲染成文本或HTML。第一阶段会创建一个中转数据结构，再把它传递给第二阶段。

### 提炼格式化阶段

可先将第二阶段的代码提炼出函数：

```js
function statement(invoice, plays) {
  return renderPlainText(invoice, plays);
}

function renderPlainText(invoice, plays) {
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(totalAmount())}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;
}
```

### 创建两个阶段的中转数据结构

创建一个对象，作为在两个阶段间传递的中转数据结构，然后将它作为第一个参数传递给renderPlainText

```js
function statement(invoice, plays) {
  let statementData = {};
  return renderPlainText(statementData, invoice, plays);
}

function renderPlainText(data, invoice, plays) {
  let result = `Statement for ${invoice.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(totalAmount())}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;
  
  function totalAmount() {...}
  function totalVolumeCredits() {...}
  function usd(aNumber) {...}
  function volumeCreditsFor(aPerformance) {...}
  function playFor(aPerformance) {...}
  function amountFor(aPerformance) {...}
}
```

接下来要做一件事，将invoice和plays中的数值全部挪到中转数据结构data中，让renderPlainText只操作通过data参数传进来的数据。

先将customer添加到中转对象中，并替换renderPlainText中对customer的引用：

```js
function statement(invoice, plays) {
  let statementData = {};
  statementData.customer = invoice.customer;
  return renderPlainText(statementData, invoice, plays);
} 

function renderPlainText(data, invoice, plays) {
  let result = `Statement for ${data.customer}\n`;
  for (let perf of invoice.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(totalAmount())}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;
  
  function totalAmount() {...}
  function totalVolumeCredits() {...}
  function usd(aNumber) {...}
  function volumeCreditsFor(aPerformance) {...}
  function playFor(aPerformance) {...}
  function amountFor(aPerformance) {...}
}
```

同样可以将performances转移过来，这样就可以删除了invoice参数：

```js
function statement(invoice, plays) {
  let statementData = {};
  statementData.customer = invoice.customer;
  statementData.performances = invoice.performanecs;
  return renderPlainText(statementData, invoice, plays);
} 

function renderPlainText(data, plays) {
  let result = `Statement for ${data.customer}\n`;
  for (let perf of data.performances) {
    // print line for this order
    result += `	${playFor(perf).name}: ${usd(amountFor(perf)) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(totalAmount())}\n}`
  result += `You earned ${totalVolumeCredits()} credits\n`;
  return result;
  
  function totalAmount() {
    let result = 0; // totalAmount
    for (let perf of data.performances) {
      result += amountFor(perf);
    }
    return result;
  }
  
  function totalVolumeCredits() {
    let result = 0; // volumeCredits
    for (let perf of data.performances) {
      result += volumeCreditsFor(perf);
    }
    return result;
  }
  function usd(aNumber) {...}
  function volumeCreditsFor(aPerformance) {...}
  function playFor(aPerformance) {...}
  function amountFor(aPerformance) {...}
}
```

接下来可以继续迁移play字段，amountFor函数，volumeCreditsFor函数，totalAmount函数和totalVolumeCredits函数。

最终通过重构后，雏形类似于下面：

```js
function statement(invoice, plays) {
  return renderPlainText(createStatementData(invoice, plays));
} 

function createStatementData(invoice, plays) {
  const result = {};
  result.customer = invoice.customer;
  result.performances = invoice.performances.map(enrichPerformance);
  result.totalAmount = totalAmount(statementData);
  result.totalVolumeCredits = totalVolumeCredits(result);
  return result;
  
  function enrichPerformance(aPerformance) {
    const result = Object.assign({}, aPerformance);
    result.play = playFor(result);
    result.amount = amountFor(result);
    result.volumeCredits = volumeCreditsFor(result);
    return result;
  }
  function totalAmount() {...}
  function totalVolumeCredits() {...}
  function volumeCreditsFor(aPerformance) {...}
  function playFor(aPerformance) {...}
  function amountFor(aPerformance) {...}
}

function renderPlainText(data) {
  let result = `Statement for ${data.customer}\n`;
  for (let perf of data.performances) {
    // print line for this order
    result += `	${perf.play.name}: ${usd(perf.amount) (${perf.audience} seats)\n}`;
  }
  result += `Amount owed is ${usd(data.totalAmount)}\n}`
  result += `You earned ${data.totalVolumeCredits} credits\n`;
  return result;
  
  function usd(aNumber) {...}
}
```

这样处理之后，渲染和获取数据分明，如果需要将renderPlainText换成renderHtml也非常容易了。

## 进展：分离到两个文件(和两个阶段)

经过上面的重构后，可以将statement、renderPlainText放在一个文件里，createStatementData放在另外一个文件里。重构使得代码可读性得到了提高。

```js
// statement.js
import createStatementData from './createStatementData.js';
function statemnet(invoice, plays) {
  return renderPlainText(createStatementData(invoice, plays));
}

function renderPlainText(data) {...}

// createStatementData.js
export default function createStatementData(invoice, plays) {
  const result = {};
  result.customer = invoice.customer;
  result.performances = invoice.performances.map(enrichPerformance);
  result.totalAmount = totalAmount(statementData);
  result.totalVolumeCredits = totalVolumeCredits(result);
  return result;
  
  function enrichPerformance(aPerformance) {
    const result = Object.assign({}, aPerformance);
    result.play = playFor(result);
    result.amount = amountFor(result);
    result.volumeCredits = volumeCreditsFor(result);
    return result;
  }
  function totalAmount() {...}
  function totalVolumeCredits() {...}
  function volumeCreditsFor(aPerformance) {...}
  function playFor(aPerformance) {...}
  function amountFor(aPerformance) {...}
}
```

## 重组计算过程

以上的重构看起来已经很完美，但还是存在一个弱点。amountFor、volumeCreditsFor函数通过枚举的方式展现计算过程，随着种类的增多，这里很容易出现代码堆积。解决这个方法可以使用面向对象世界里的经典特性—**类型多态**。

该重构方法为**以多态取代条件表达式(272)**，将多个同样的类型码分支用多态取代。在施展之前，得先创建一个基本的继承结构。

其实经过上面将展示和计算分文件存储可以知道，只需要对createStatementData.js文件进行重构即可。而重构的关键在enrichPerformance、amountFor、volumeCreditsFor函数上。

### 创建计算器

要使amountFor、volumeCreditsFor函数中不因为类型的增加而频繁的修改代码，可以在enrichPerformance中统一创建一个PerformanceCalculator对象，PerformanceCalculator是一个类，通过该对象来处理所有需要的参数：

```js
function enrichPerformance(aPerformance) {
  const calculator = new PerformanceCalculator(aPerformance, playFor(aPerformance));
  const result = Object.assign({}, aPerformance);
  result.play = calculator.play;
  result.amount = amountFor(result);
  result.volumeCredits = volumeCreditsFor(result);
  return result;
}

class PerformanceCalculator {
  constructor(aPerformance, aPlay) {
    this.performance = aPerformance;
    this.play = aPlay;
  }
}
```

### 将函数也迁移到计算器

实际上，这部分才是做多态处理的关键，因为并不想将复杂的业务逻辑呈现在代码中，于是把amountFor、volumeCreditsFor函数搬入到计算器：

```js
function enrichPerformance(aPerformance) {
  const calculator = new PerformanceCalculator(aPerformance, playFor(aPerformance));
  const result = Object.assign({}, aPerformance);
  result.play = calculator.play;
  result.amount = calculator.amount;
  result.volumeCredits = calculator.volumeCredits;
  return result;
}

class PerformanceCalculator {
  constructor(aPerformance, aPlay) {
    this.performance = aPerformance;
    this.play = aPlay;
  }
  
  get amount() {
    let result = 0;
    switch (this.play.type) {
      case 'tragedy':
        result = 40000;
        if (this.performance.audience > 30) {
          result += 1000 * (this.performance.audience - 30);
        }
        break;
      case 'comedy':
        result = 30000;
        if (this.performance.audience > 20) {
          result += 10000 + 500 * (this.performance.audience - 20);
        }
        result += 300 * this.performance.audience;
        break;
      default:
        throw new Error(`unknown type: ${this.play.type}`);
    }
    return result;
  }
  
  get volumeCredits() {
    let result = 0;
    result += Math.max(this.performance.audience - 30, 0);
    if ('comedy' === this.play.type) result += Math.floor(this.performance.audience / 5);
    return result;
  }
}
```

### 计算器加入多态性

不难看出，上面也只是将amountFor、volumeCreditsFor函数挪了一个位置。实质上并没有发生变化。既然已经提出了amount和volumeCredits到class中，可以使用class的继承特性，创建子类继承自PerformanceCalculator类，然后拆解PerformanceCalculator中的amount和volumeCredits到对应的子类中，这样就可以使用**以工厂函数取代构造函数(334)**。

```js
function enrichPerformance(aPerformance) {
  const calculator = new createPerformanceCalculator(aPerformance, playFor(aPerformance)); // 替换该函数为createPerformanceCalculator，意在作为PerformanceCalculator的共产函数
  const result = Object.assign({}, aPerformance);
  result.play = calculator.play;
  result.amount = calculator.amount;
  result.volumeCredits = calculator.volumeCredits;
  return result;
}

// 工厂函数
function createPerformanceCalculator(aPerformance, aPlay) {
  switch (aPlay.type) {
    case "tragedy": return new TragedyCalculator(aPerformance, aPlay);
    case "comedy": return new ComedyCalculator(aPerformance, aPlay);
    defualt: throw new Error(`unknown type: ${aPlay.type}`);
  }
}

class TragedyCalculator extends PerformanceCalculator {
  get amount() {
    let result = 40000;
    if (this.performance.audience > 30) {
      result += 1000 * (this.performance.audience - 30);
    }
    return result;
  }
}

class ComedyCalculator extends PerformanceCalculator {
  get amount() {
    let result = 30000;
    if (this.performance.audience > 20) {
      result += 10000 + 500 * (this.performance.audience - 20);
    }
    result += 300 * this.performance.audience;
    return result;
  }
  
  get volumeCredits() {
    return super.volumeCredits + Math.floor(this.performance.audience / 5);
  }
}

class PerformanceCalculator {
  constructor(aPerformance, aPlay) {
    this.performance = aPerformance;
    this.play = aPlay;
  }
  
  get amount() {
    throw new Error(`unknown type: ${this.play.type}`);
  }
  
  get volumeCredits() {
    return  Math.max(this.performance.audience - 30, 0);
  }
}
```

通过这样的新结构改进，不同种类的计算各自集中到了一处地方。当添加新的剧种时，只需要添加一个子类，并在创建函数中返回它。实际上越多的函数依赖于同一套类型进行多态，这种继承方案就越有益处。

## 总结

以上例子其实已经看出重构的威力，代码层次清晰且方便扩展。有3个重要的重构技巧使用：**将原函数分解成一组嵌套的函数、应用拆分阶段分离计算逻辑与输出格式化逻辑，以及为计算器引入多态性进来处理计算逻辑**。

一般来说，重构早起的主要动力是尝试理解代码如何工作。清晰的代码更容易理解，能够发现更深层次的设计问题，从而形成积极正向的反馈环。

作者认为，**好代码的检验标准就是人们是否能轻而易举地修改它**。好代码应该直截了当：有人需要修改代码时，他们应能轻易找到修改点，应该能快速做出更改，而不易引入其他错误。

开展高效有序的重构，关键的心得是：**小的步子可以更快前进，保持代码永远处于可工作状态，小步修改积累起来也能大大改善系统的设计**。

