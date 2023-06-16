#include "val.h"


// THIS IS NOT THE var.h FILE BTW
//repeat string of this object op number of times
Value Value::operator-(const Value& op)const{
string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
        return Value(GetReal()-op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
        return Value(GetInt()-op.GetReal());
    }
   else if(IsReal()&&op.IsInt()){
        return Value(GetReal()-op.GetInt());
    }

    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stod(a)-GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)-GetInt());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }

    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stod(a)-op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
     else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)-op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                return Value(stod(b)+stod(a));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
}
Value Value::operator+(const Value& op)const{
string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
        return Value(GetReal()+op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
        return Value(GetInt()+op.GetReal());
    }
   else if(IsReal()&&op.IsInt()){
        return Value(GetReal()+op.GetInt());
    }

    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stod(a)+GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)+GetInt());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }

    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stod(a)+op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
     else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)+op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                return Value(stod(b)+stod(a));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
}
Value Value::operator/(const Value& op)const{
string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
         if(op.GetReal()==0){return Value();}
        return Value(GetReal()/op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
         if(op.GetReal()==0){return Value();}
        return Value(GetInt()/op.GetReal());
    }
   else if(IsReal()&&op.IsInt()){
     if(op.GetInt()==0){return Value();}
        return Value(GetReal()/op.GetInt());
    }

    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
             if(stod(a)==0){return Value();}
            return Value(stod(a)/GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
                 if(stod(a)==0){return Value();}
            return Value(GetInt()/stoi(a));
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }

    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
                 if(op.GetReal()==0){return Value();}
            return Value(stod(a)/op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
     else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
                 if(op.GetInt()==0){return Value();}
            return Value(stoi(a)/op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                if(stod(b)==0){return Value();}
                return Value(stod(a)/stod(b));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
}
Value Value::operator>(const Value& op)const{

   string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
        return Value(GetReal()>op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
        return Value(GetInt()>op.GetReal());
    }
   if(IsReal()&&op.IsInt()){
        return Value(GetReal()>op.GetInt());
    }
       if(IsInt()&&op.IsInt()){
        return Value(GetInt()>op.GetInt());
    }

    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)>GetInt());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stod(a)>GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stod(a)>op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)>op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                return Value(stod(b)>stod(a));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
    }



    
Value Value::operator<(const Value& op)const{

   string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
        return Value(GetReal()<op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
        return Value(GetInt()<op.GetReal());
    }
   if(IsReal()&&op.IsInt()){
        return Value(GetReal()<op.GetInt());
    }
       if(IsInt()&&op.IsInt()){
        return Value(GetInt()<op.GetInt());
    }

    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)<GetInt());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stod(a)<GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stod(a)<op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)<op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                return Value(stod(b)<stod(a));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
    }


    
    

Value Value::Repeat(const Value& op) const {
    //First operands is a string and the second operand is an integer
    double oper;
    if(IsString() && op.IsString()){
        //second operand must be converted to a numeric
        try {
            oper = stod(op.GetString());
        }
        catch(invalid_argument & arg){
            cout << "Iiiiinvalid conversion from string to double." << endl;
            return Value();
        }
        int times = oper;
        string str = GetString(), newstr = "";
        for(int i = 1; i <= times; i++){
            newstr += str;
        }
        return Value(newstr);
    }
    
    else if (IsString() && op.IsReal()){
        oper = op.GetReal();
        int times = oper;
        string str = GetString(), newstr = "";
        for(int i = 1; i <= times; i++){
            newstr += str;
        }
        return Value(newstr);
    }
    else {
        return Value();
    }
}
Value Value::operator*(const Value& op)const{
   string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
        return Value(GetReal()*op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
        return Value(GetInt()*op.GetReal());
    }
   else if(IsReal()&&op.IsInt()){
        return Value(GetReal()*op.GetInt());
    }

    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stod(a)*GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)*GetInt());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }

    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stod(a)*op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
     else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)*op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                return Value(stod(b)*stod(a));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
    }


Value Value::operator==(const Value& op)const{

   string a="";
   string b="";
    if(IsReal()&&op.IsReal()){
        return Value(GetReal()==op.GetReal());
    }
    else if(IsInt()&&op.IsReal()){
        return Value(GetInt()==op.GetReal());
    }
   if(IsReal()&&op.IsInt()){
        return Value(GetReal()==op.GetInt());
    }
       if(IsInt()&&op.IsInt()){
        return Value(GetInt()==op.GetInt());
    }

    else if(IsInt()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)==GetInt());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsReal()&& op.IsString()){
        a= op.GetString();
        if(isdigit(a[0])){
            return Value(stod(a)==GetReal());
        }
        else{

            cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    }
    else if(IsString()&&op.IsReal()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stod(a)==op.GetReal());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsInt()){
    a=GetString();
        if(isdigit(a[0])){
            return Value(stoi(a)==op.GetInt());
            
        }
        else{
             cout<<"Invalid conversion from string to double."<<endl;
            return Value();}
    
    
    }
    else if(IsString()&&op.IsString()){
            a=GetString();
            b=op.GetString();
            if(isdigit(a[0])&&isdigit(b[0])){
                return Value(stod(b)==stod(a));
            }
            else {
                 cout<<"Invalid conversion from string to double."<<endl;
                return Value();}
    }
    return Value();
    
    
    }


    


Value Value::operator^(const Value& op)const{


    if(IsReal() && op.IsReal()) {return pow(GetReal(),op.GetReal());} 
    else if(IsInt() && op.IsReal()) {return pow(GetInt(),op.GetReal());} 
     if(IsReal() && op.IsInt()) {return pow(GetReal(),op.GetInt());} 
      if(IsInt() && op.IsInt()) {return pow(GetInt(),op.GetInt());} 

     else{
        
        
        return Value();}
}
Value Value::Catenate(const Value& op)const{

 string a="";
   string b="";
   if(IsInt()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        stroper1+=outStr2.str();
      
        return Value(stroper1);
    }
       else if(IsInt()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        stroper1+=outStr2.str();
      
        return Value(stroper1);
    }
        else if(IsReal()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        stroper1+=outStr2.str();
      
        return Value(stroper1);
    }
    else if(IsReal()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        stroper1+=outStr2.str();
      
        return Value(stroper1);
    }

    else if(IsInt()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetInt();
     
        string stroper1 = outStr1.str();
        stroper1+=op.GetString();
        return Value(stroper1);
    }
    else if(IsReal()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetReal();
     
        string stroper1 = outStr1.str();
        stroper1+=op.GetString();
        return Value(stroper1);
    }
        
    else if(IsString()&&op.IsReal()){
     ostringstream outStr1;
        outStr1 << op.GetReal();
     
        string stroper1 = GetString();
        stroper1+=outStr1.str();
        return Value(stroper1);
    
    }
    else if(IsString()&&op.IsInt()){
     ostringstream outStr1;
        outStr1 << op.GetInt();
     
        string stroper1 = GetString();
        stroper1+=outStr1.str();
        return Value(stroper1);
    
    }
    else if(IsString()&&op.IsString()){
         string p=GetString()+op.GetString();
                return Value(p);
    }
    return Value();
    


}
Value Value::SEqual(const Value& op)const{
bool flag=false;
    if(IsInt()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    }
    else if(IsReal()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    }
    else if(IsInt()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    }
     else if(IsReal()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    }
    else if(IsInt()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetInt();
     
        string stroper1 = outStr1.str();
        string stroper2=op.GetString();
       if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    }

    else if(IsReal()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetReal();
     
        string stroper1 = outStr1.str();
        string stroper2=op.GetString();
       if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    }
        
    else if(IsString()&&op.IsReal()){
     ostringstream outStr1;
        outStr1 << op.GetReal();
     
        string stroper1 = GetString();
        string stroper2=outStr1.str();
       if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    
    }
     else if(IsString()&&op.IsInt()){
     ostringstream outStr1;
        outStr1 << op.GetInt();
     
        string stroper1 = GetString();
        string stroper2=outStr1.str();
       if(stroper1.compare(stroper2)==0){flag=true;}
      
        return Value(flag);
    
    }
    else if(IsString()&&op.IsString()){
         string p=GetString();
         string o=op.GetString();
                if(p.compare(o)==0){flag=true;}
      
        return Value(flag);
    }
    return Value();
    
}
Value Value:: SGthan(const Value& op)const{
bool flag=false;
    if(IsInt()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    }
    else if(IsReal()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    }
    else if(IsInt()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    }
     else if(IsReal()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    }
    else if(IsInt()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetInt();
     
        string stroper1 = outStr1.str();
        string stroper2=op.GetString();
       if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    }

    else if(IsReal()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetReal();
     
        string stroper1 = outStr1.str();
        string stroper2=op.GetString();
       if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    }
        
    else if(IsString()&&op.IsReal()){
     ostringstream outStr1;
        outStr1 << op.GetReal();
     
        string stroper1 = GetString();
        string stroper2=outStr1.str();
       if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    
    }
     else if(IsString()&&op.IsInt()){
     ostringstream outStr1;
        outStr1 << op.GetInt();
     
        string stroper1 = GetString();
        string stroper2=outStr1.str();
       if(stroper1.compare(stroper2)>0){flag=true;}
      
        return Value(flag);
    
    }
    else if(IsString()&&op.IsString()){
         string p=GetString();
         string o=op.GetString();
                if(p.compare(o)>0){flag=true;}
      
        return Value(flag);
    }
    return Value();
    
}
Value Value:: SLthan(const Value& op)const{
bool flag=false;
    if(IsInt()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    }
    else if(IsReal()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    }
    else if(IsInt()&&op.IsReal()){
        ostringstream outStr2;
        outStr2 << op.GetReal();
        ostringstream outStr1;
        outStr1 << GetInt();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    }
     else if(IsReal()&&op.IsInt()){
        ostringstream outStr2;
        outStr2 << op.GetInt();
        ostringstream outStr1;
        outStr1 << GetReal();
        string stroper1 = outStr1.str();
        string stroper2=outStr2.str();
      if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    }
    else if(IsInt()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetInt();
     
        string stroper1 = outStr1.str();
        string stroper2=op.GetString();
       if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    }

    else if(IsReal()&& op.IsString()){
        ostringstream outStr1;
        outStr1 << GetReal();
     
        string stroper1 = outStr1.str();
        string stroper2=op.GetString();
       if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    }
        
    else if(IsString()&&op.IsReal()){
     ostringstream outStr1;
        outStr1 << op.GetReal();
     
        string stroper1 = GetString();
        string stroper2=outStr1.str();
       if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    
    }
     else if(IsString()&&op.IsInt()){
     ostringstream outStr1;
        outStr1 << op.GetInt();
     
        string stroper1 = GetString();
        string stroper2=outStr1.str();
       if(stroper1.compare(stroper2)<0){flag=true;}
      
        return Value(flag);
    
    }
    else if(IsString()&&op.IsString()){
         string p=GetString();
         string o=op.GetString();
                if(p.compare(o)<0){flag=true;}
      
        return Value(flag);
    }
    return Value();
    


}