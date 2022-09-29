# smstools3

基于smstools3-3.1.2, 增加了CDMA短信发送对应。

## 背景

公司的GSM短信猫更换成4G LTE猫以后，发现用电信的SIM卡无法用之前一直用的smstools3发送短信。

经过一番调查，发现原因是电信的短信标准是基于CDMA的，和GSM的短信标准差异巨大，而smstools3的作者明确表明不会支持CDMA格式的短信。

网上能找到一些CDMA短信PDU的编码和解码代码，但只有JavaScript和Java的，没有C的代码可以直接拿来修改使用。

为了支持使用电信CDMA格式的短信发送，在smstools3-3.1.2的基础上对代码进行了简单的修改，采用调用nodeJS执行JavaScript的方式将短信内容编码为CDMA格式的PDU，然后由smstoolsd通过短信猫发送。
这样就可以避免用C重写smstools3里的PDU编码代码。

上述修改后，Zabbix可以继续用现有的脚本发送告警短信。只是短信内容只支持英文字符。

如果需要实现中文的短信发送，可以用CDMASMS.js将文本先编码成PDU，然后在短信定义文件中设置`Text_is_pdu: true`，将CDMA的短信编码结果PDU直接交给smstools发送，跳过smstools的内部PDU处理从而实现发送中文短信。

这种方式的短信定义文件样本如下：

```
To: 123456789
Text_is_pdu: true

0000021002040702C629859E0A200601FC082600032000100114204AE1E39CDFF862A01CCB8A7433248BB42180100306220828173216080100
```

注意：PDU的HEX字符串必须是全部大写。

## 限制

考虑到目前只需要发送短信，所以CDMA短信的解码没有对应。