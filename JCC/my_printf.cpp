class FormatParm{

public:
    enum Type {
        Type_int,
        Type_double,
    };
    
    const void* p;
    Type var_type;
    
    FormatParm(const int& i){
        p = &i;
        var_type = Type_int;
    }
    
    FormatParm(double d){
        //
    }
};

class FormatParmArray{
    FormatParm* fparm;
    
};

void my_printf(const char* fmt, const FormatParm& p0, FormatParm p1) {
    //
}
