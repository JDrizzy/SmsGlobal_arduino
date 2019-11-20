Version: 0.0.1

Arduino library to send SMS message using service SMS Global - https://www.smsglobal.com/

# 1. Create class instance

SmsGlobal smsGlobal(sms_global_user, sms_global_password);

# 2. Send SMS message

smsGlobal.send("ESP2866", sms_to, "Hello!");
