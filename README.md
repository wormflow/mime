# mime
mime:unmime study fetchmail clone from apple opensource

string handMainFile(string strMainFile){
    string DecodeAns="";
    string LineString="";
    string StringNeedToDecode="";
    string boundaryString="";
    bool isMime = false;
    //∂¡»°º”√‹¿‡–Õ
    char EncodeType='8';
    char CharsetString='u';
    stringstream needPstring;
    needPstring.str(strMainFile);
    int first_p;
    while(std::getline(needPstring,LineString)&&LineString!=""){
    // ÷ª”–‘⁄MIME-Versionµƒ ±∫Ú≤≈Ω¯––Ω‚Œˆ
        if(( LineString.find("MIME-Version: 1.0")!=-1)||(LineString.find("Mime-Version: 1.0")!=-1)||( LineString.find("MIME-version: 1.0")!=-1)){
            //π˛π˛–¬µƒ“ª––£°£°£°
                isMime = true;
        }
        if(isMime){
            //std::getline(needPstring,LineString);
            //ø¥ø¥”–√ª”–±ﬂΩÁ
            if((first_p=(LineString.find("boundary="))!=-1)){
                if(LineString[first_p+1]=='\"'){
                    int last_p;
                    last_p=LineString.rfind("\"");
                    boundaryString = LineString.substr(first_p+10,last_p-first_p+10);
                }else{
                    boundaryString = LineString.substr(first_p+9);
                }
            }
        }
    } 

    while(std::getline(needPstring,LineString)){
        if(LineString.find("Content-Transfer-Encoding:")!=-1){
            first_p=LineString.find("Content-Transfer-Encoding:")+27;
            EncodeType=LineString[first_p];
        }
        if(LineString.find("charset=")!=-1){
            first_p=LineString.find("charset=")+10;
            EncodeType=LineString[first_p];
        }
        StringNeedToDecode="";
        while(std::getline(needPstring,LineString)){
            if(LineString.find(boundaryString)!=-1){
                StringNeedToDecode+=LineString;
            }else{
                DecodeAns+=DecodeiMail(StringNeedToDecode,'8','u');
                break;
            }

        }
    }
    return DecodeAns;
}

string DecodeiMail(string StringNeedToDecode,char decodeType,char charsetType){
    string ans=StringNeedToDecode;
    
    return ans;
}

