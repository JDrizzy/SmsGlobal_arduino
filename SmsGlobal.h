#ifndef SmsGlobal_h
#define SmsGlobal_h

#include <Arduino.h>

class SmsGlobal {
	private:
		String _user, _password;
		String urlEncode(String value);
	public:
		SmsGlobal(String user, String password);
		bool send(String from, String to, String text);
};

#endif
