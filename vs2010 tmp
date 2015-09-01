#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cerrno>
using namespace std;

//base64
#include <ctype.h>

static const char base64digits[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define BAD	-1
static const char base64val[] = {
	BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD,
	BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD,
	BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, BAD, 62, BAD, BAD, BAD, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, BAD, BAD, BAD, BAD, BAD, BAD,
	BAD, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, BAD, BAD, BAD, BAD, BAD,
	BAD, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, BAD, BAD, BAD, BAD, BAD
};
#define DECODE64(c)  (isascii((unsigned char)(c)) ? base64val[c] : BAD)

void to64frombits(char *out, const void *in_, int inlen)
/* raw bytes in quasi-big-endian order to base 64 string (NUL-terminated) */
{
	const unsigned char *in = (const unsigned char *)in_;

	for (; inlen >= 3; inlen -= 3)
	{
		*out++ = base64digits[in[0] >> 2];
		*out++ = base64digits[((in[0] << 4) & 0x30) | (in[1] >> 4)];
		*out++ = base64digits[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
		*out++ = base64digits[in[2] & 0x3f];
		in += 3;
	}
	if (inlen > 0)
	{
		unsigned char fragment;

		*out++ = base64digits[in[0] >> 2];
		fragment = (in[0] << 4) & 0x30;
		if (inlen > 1)
			fragment |= in[1] >> 4;
		*out++ = base64digits[fragment];
		*out++ = (inlen < 2) ? '=' : base64digits[(in[1] << 2) & 0x3c];
		*out++ = '=';
	}
	*out = '\0';
}

int from64tobits(void *out_, const char *in, int maxlen)
/* base 64 to raw bytes in quasi-big-endian order, returning count of bytes */
/* maxlen limits output buffer size, set to zero to ignore */
{
	int len = 0;
	register unsigned char digit1, digit2, digit3, digit4;
	unsigned char *out = (unsigned char *)out_;

	if (in[0] == '+' && in[1] == ' ')
		in += 2;
	if (*in == '\r')
		return(0);

	do {
		digit1 = in[0];
		if (DECODE64(digit1) == BAD)
			return(-1);
		digit2 = in[1];
		if (DECODE64(digit2) == BAD)
			return(-1);
		digit3 = in[2];
		if (digit3 != '=' && DECODE64(digit3) == BAD)
			return(-1);
		digit4 = in[3];
		if (digit4 != '=' && DECODE64(digit4) == BAD)
			return(-1);
		in += 4;
		++len;
		if (maxlen && len > maxlen)
			return(-1);
		*out++ = (DECODE64(digit1) << 2) | (DECODE64(digit2) >> 4);
		if (digit3 != '=')
		{
			++len;
			if (maxlen && len > maxlen)
				return(-1);
			*out++ = ((DECODE64(digit2) << 4) & 0xf0) | (DECODE64(digit3) >> 2);
			if (digit4 != '=')
			{
				++len;
				if (maxlen && len > maxlen)
					return(-1);
				*out++ = ((DECODE64(digit3) << 6) & 0xc0) | DECODE64(digit4);
			}
		}
	} while
		(*in && *in != '\r' && digit4 != '=');

	return (len);
}

/* base64.c ends here */

//
string DecodeiMail(string StringNeedToDecode, char decodeType, char charsetType);

string handMainFile(string strMainFile){
	string DecodeAns = "";
	string LineString = "";
	string StringNeedToDecode = "";
	string boundaryString = "";
	bool isMime = false;
	//???°o”√???–?
	char EncodeType = '8';
	char CharsetString = 'u';
	stringstream needPstring;
	needPstring.str(strMainFile);
	int first_p;
	while (std::getline(needPstring, LineString) && LineString != ""){
		// ÷a”–‘?MIME-Versionμ? ±∫ú≤≈Ωˉ––Ω???
		if ((LineString.find("MIME-Version: 1.0") != -1) || (LineString.find("Mime-Version: 1.0") != -1) || (LineString.find("MIME-version: 1.0") != -1)){
			//π?π?–?μ?“a––￡°￡°￡°
			isMime = true;
		}
		if (isMime){
			//std::getline(needPstring,LineString);
			//?￥?￥”–√a”–±?Ωá
			if ((first_p = (LineString.find("boundary=")) != -1)){
				if (LineString[first_p + 9] == '\"'){
					int last_p;
					last_p = LineString.rfind("\"");
					boundaryString = LineString.substr(first_p + 10, 10);//取10位可以容错
				}
				else{
					boundaryString = LineString.substr(first_p + 9,10);
				}
			}
		}
	}
	//find first line!!!
	bool isNullLine = false;
	while (std::getline(needPstring, LineString)){
		if (LineString.find("charset=") != -1){
			first_p = LineString.find("charset=") + 8;
			CharsetString = LineString[first_p];
		}
		if (LineString.find("Content-Transfer-Encoding:") != -1){
			first_p = LineString.find("Content-Transfer-Encoding:") + 27;
			EncodeType = LineString[first_p];
		}
		StringNeedToDecode = "";
		//
		if (LineString == "") isNullLine = true;
		if(isNullLine){
			while (std::getline(needPstring, LineString)){
				//not find
				if (LineString.find(boundaryString) == -1){
					if (LineString != "") {
						StringNeedToDecode += LineString;
					}
					else{
						StringNeedToDecode += '\n';
					}
				}
				else{
					//output it
					DecodeAns += DecodeiMail(StringNeedToDecode, 'b', 'u');
					isNullLine = false;
					char EncodeType = '8';
					char CharsetString = 'u';
					break;
				}
			}//while
		}
	}
	return DecodeAns;
}

string DecodeiMail(string StringNeedToDecode, char decodeType, char charsetType){
	string ans = "";
	char cans[4096];
	if (decodeType == 'b'){
		from64tobits(cans, StringNeedToDecode.c_str(), StringNeedToDecode.size()+1);
			ans = cans;
	}
	return ans;
}

std::string get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

int main(){
	string a;
	a = get_file_contents("e:\\111.emlx");
	string ans;
	ans = handMainFile(a);
	printf("%s", ans);
	return 0;
}
