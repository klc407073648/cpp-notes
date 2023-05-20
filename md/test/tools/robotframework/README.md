# 测试工具 -RobotFramework

# 学习网站

* [用户指导手册, Robot Framework User Guide](http://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html)
* [robotframework官网](https://robotframework.org/)
* [自动化测试框架, robotframework/RIDE](https://github.com/robotframework/RIDE)
* [web测试库, SeleniumLibrary](http://robotframework.org/SeleniumLibrary/SeleniumLibrary.html)

# 指导

## python安装requirements.txt文件

requirements.txt为pip安装内容列表

```
pip install -r requirements.txt
```

https://github.com/MarketSquare/robotframework-requests

2.2.2   Using arguments

2.2.7  Test templates

pip install robotframework-sshlibrary

https://github.com/up1/course-robotframework

python安装requirements.txt文件：
pip install -r requirements.txt

中文乱码解决：

找到Python路径下的testrunnerplugin.py文件，如我的文件路径：C:\Python\Python37\Lib\site-packages\robotide\contrib\testrunner\testrunnerplugin.py

将第565行的encoding['SYSTEM']改为encoding['OUTPUT']，如下图

```python
textctrl.SetReadOnly(False)
        try:
            if enc:
                textctrl.AppendText(string.encode(encoding['SYSTEM']))
            else:
                textctrl.AppendText(string)
            # print("DEBUG _AppendText Printed OK")
        except UnicodeDecodeError as e:
            # I'm not sure why I sometimes get this, and I don't know what I
            # can do other than to ignore it.
            if PY2:
                if is_unicode(string):
                    textctrl.AppendTextRaw(bytes(string.encode('utf-8')))
                else:
                    textctrl.AppendTextRaw(string)
            else:
                textctrl.AppendTextRaw(bytes(string, encoding['SYSTEM'])) #encoding['SYSTEM']改为encoding['OUTPUT']
```
