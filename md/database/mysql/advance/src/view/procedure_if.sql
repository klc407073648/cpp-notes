-- if
-- 根据定义的分数score变量，判定当前分数对应的分数等级。
-- score >= 85分，等级为优秀。
-- score >= 60分 且 score < 85分，等级为及格。
-- score < 60分，等级为不及格。

create procedure p3()
begin
    declare score int default 58;
    declare result varchar(10);

    if score >= 85 then
        set result := '优秀';
    elseif score >= 60 then
        set result := '及格';
    else
        set result := '不及格';
    end if;
    select result;
end;

call p3();