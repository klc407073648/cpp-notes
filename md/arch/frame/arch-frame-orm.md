# 架构 - ORM框架

[[toc]]

# 参考资料

- [wiki百科ORM框架](https://en.wikipedia.org/wiki/Object-3relational_mapping)

# wiki百科概念

> Object–relational mapping (ORM, O/RM, and O/R mapping tool) in computer science is a programming technique for **converting data between type systems** using object-oriented programming languages. This creates, in effect, a "virtual object database" that can be used from within the programming language. There are both free and commercial packages available that **perform object–relational mapping**, although some programmers opt to construct their own ORM tools.

In object-oriented programming, data-management tasks act on objects that are almost always non-scalar values. For example, consider an address book entry that represents a single person along with zero or more phone numbers and zero or more addresses. This could be modeled in an object-oriented implementation by a "Person object" with an attribute/field to hold each data item that the entry comprises: the person's name, a list of phone numbers, and a list of addresses. The list of phone numbers would itself contain "PhoneNumber objects" and so on. Each such address-book entry is treated as a single object by the programming language (it can be referenced by a single variable containing a pointer to the object, for instance). **Various methods can be associated with the object**, such as methods to return the preferred phone number, the home address, and so on.

By contrast, many popular database products, such as SQL, are not object-oriented and can only store and manipulate scalar values such as integers and strings organized within tables. The programmer must either **convert the object values into groups of simpler values for storage in the database** (and convert them back upon retrieval), or only use simple scalar values within the program. Object–relational mapping implements the first approach.

The heart of the problem involves translating the logical representation of the objects into an atomized form that is capable of being stored in the database while preserving the properties of the objects and their relationships so that they can be reloaded as objects when needed. If this storage and retrieval functionality is implemented, the objects are said to be persistent.

* 对象转换成数据库字段**存储**和维护对象和关联关系便于从数据库字段**转回**成对象，从而实现持久化。

## Comparison with traditional data access techniques

Compared to traditional techniques of exchange between an object-oriented language and a relational database, ORM often reduces the amount of code that needs to be written.

* 使用ORM框架，可以减少大量代码的编写

Disadvantages of ORM tools generally stem from the high level of abstraction obscuring what is actually happening in the implementation code. Also, heavy reliance on ORM software has been cited as a major factor in producing poorly designed databases.

* 高度抽象，模糊实际的代码实现(由框架生成)
* 严重依赖ORM软件导致不良的数据库设计

## Object-oriented databases

Another approach is to use an object-oriented database management system (OODBMS) or document-oriented databases such as native XML databases that provide more flexibility in data modeling. OODBMSs are databases designed specifically for working with object-oriented values. Using an OODBMS eliminates the need for converting data to and from its SQL form, as the data is stored in its original object representation and relationships are directly represented, rather than requiring join tables/operations. The equivalent of ORMs for document-oriented databases are called object-document mappers (ODMs).

Document-oriented databases also prevent the user from having to "shred" objects into table rows. Many of these systems also support the XQuery query language to retrieve datasets.

Object-oriented databases tend to be used in complex, niche applications. One of the arguments against using an OODBMS is that it may not be able to execute ad-hoc, application-independent queries.For this reason, many programmers find themselves more at home with an object-SQL mapping system, even though most object-oriented databases are able to process SQL queries to a limited extent. Other OODBMS provide replication to SQL databases, as a means of addressing the need for ad-hoc queries, while preserving well-known query patterns.

* 使用面向对象的数据库管理系统（OODBMS）
    * 无需将数据转换为SQL形式，因为数据存储在其原始对象表示中，关系直接表示，而不需要连接表/操作。
* 面向文档的数据库(ODM)
    * 防止用户将对象“分解”为表行。

## Challenges

A variety of difficulties arise when considering how to **match an object system to a relational database**. These difficulties are referred to as the object–relational impedance mismatch.

An alternative to implementing ORM is use of the native procedural languages provided with every major database. These can be called from the client using SQL statements. The Data Access Object (DAO) design pattern is used to abstract these statements and offer a lightweight object-oriented interface to the rest of the application.

* 实现ORM的另一种方法是使用每个主要数据库提供的本地过程语言。
    * 可以使用SQL语句从客户端调用。
    * 数据访问对象（DAO）设计模式用于抽象这些语句，并为应用程序的其余部分提供轻量级的面向对象接口。


# 什么是ORM

> 对象关系映射（Object Relational Mapping，简称ORM）模式是一种为了解决**面向对象与关系数据库存在的互不匹配**的现象的技术。ORM框架是连接数据库的桥梁，只要提供了**持久化类与表的映射关系**，ORM框架在运行时就能参照映射文件的信息，把对象持久化到数据库中。

ORM框架：为了解决面型对象与关系数据库存在的互不匹配的现象的框架。

当前ORM框架主要有五种：

1. Hibernate 全自动 需要写hql语句
2. iBATIS 半自动 自己写sql语句,可操作性强,小巧
3. MyBatis
4. EclipseLink 一个可扩展的支持JPA的ORM框架，供强大的缓存功能，缓存支持集群。
5. JFinal

## 为什么使用ORM

当实现一个应用程序时（不使用O/R Mapping），可能会写特别多数据访问层的代码，从数据库保存、删除、读取对象信息，而这些代码都是重复的。而使用ORM则会大大减少重复性代码。

对象关系映射（Object Relational Mapping，简称ORM），主要实现程序对象到关系数据库数据的映射。

| 面向对象概念| 	面向关系概念| 
|:-------------:| -----:|
| 类	| 表| 
| 对象	| 表的行(记录)| 
| 属性	| 表的列(字段)| 


**对象-关系映射解释：**

1. 简单：ORM以最基本的形式建模数据。比如ORM会将MySQL的一张表映射成一个Java类（模型），表的字段就是这个类的成员变量
2. 精确：ORM使所有的MySQL数据表都按照统一的标准精确地映射成java类，使系统在代码层面保持准确统一
3. 易懂：ORM使数据库结构文档化。比如MySQL数据库就被ORM转换为了java程序员可以读懂的java类，java程序员可以只把注意力放在他擅长的java层面（当然能够熟练掌握MySQL更好）
4. 易用：ORM包含对持久类对象进行CRUD操作的API，例如create(), update(), save(), load(), find(), find_all(), where()等，也就是讲sql查询全部封装成了编程语言中的函数，通过函数的链式组合生成最终的SQL语句。通过这种封装避免了不规范、冗余、风格不统一的SQL语句，可以避免很多人为Bug，方便编码风格的统一和后期维护。

## ORM的优缺点

优点：

1. 提高开发效率，降低开发成本
2. 使开发更加对象化
3. 可移植
4. 可以很方便地引入数据缓存之类的附加功能

缺点：

1. 自动化进行关系数据库的映射需要消耗系统性能。其实这里的性能消耗还好啦，一般来说都可以忽略之。
2. 在处理多表联查、where条件复杂之类的查询时，ORM的语法会变得复杂。
