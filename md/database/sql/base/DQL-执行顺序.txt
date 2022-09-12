查询年龄大于15的员工姓名、年龄，并根据年龄进行升序排序。
	select name , age from emp where age <= 35 order by age asc , entrydate desc;

在查询时，我们给emp表起一个别名 e，然后在select 及 where中使用该别名。
	select e.name , e.age from emp e where e.age > 15 order by age asc;

执行上述SQL语句后，我们看到依然可以正常的查询到结果，此时就说明： from 先执行, 然后
where 和 select 执行。那 where 和 select 到底哪个先执行呢?

此时我们可以给select后面的字段起别名，然后在 where 中使用这个别名，然后看看是否可以执行成功。执行上述SQL报错了:eage找不到
	select e.name ename , e.age eage from emp e where eage > 15 order by age asc;

由此我们可以得出结论: from 先执行，然后执行 where ， 再执行select 。
	select e.name ename , e.age eage from emp e where e.age > 15 order by eage asc;

接下来，我们再执行如下SQL语句，查看执行效果：结果执行成功。 

那么也就验证了: order by 是在select 语句之后执行的。

综上所述，我们可以看到DQL语句的执行顺序为： from ... where ... group by ...having ... select ... order by ... limit ...