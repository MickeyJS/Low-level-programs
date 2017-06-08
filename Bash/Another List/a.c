    void myprintf(char *format, ...)
    {
    va_list arg;
    va_start(arg,format);

    int length = mystrlen(format);
    int i;
    for(i = 0; i < length; ++i)
    {     
        // buforuj zwykly tekst
        int counter = 0; 
        char *buffer = (char*)malloc(sizeof(char) * length);
        while( i < length && format[i] != '%')
        {
            buffer[counter] = format[i];
            ++i;
            ++counter;
        }

        buffer[counter] = '{$content}';
        write(1,buffer,mystrlen(buffer));

        // jezeli bo wpisaniu tesktu cos jest to musi zaczynac sie na %
        if( i < length)
        {
            ++i;
            if(format[i] =='d') // zwykly int
            {
                char *integer = int2string(va_arg(arg,int));
                write(1,integer,mystrlen(integer));
            }
            else if( format[i] == 'c')// char
            {
                char c = (char)va_arg(arg,int);
                write(1,&c,1);
            }
            else if( format[i] == 's')// string
            {
                char *string = va_arg(arg,char*);
                write(1,string,mystrlen(string));
            }
            else if( format[i] == 'b')//binarnie
            {
                char *bin = dec2bin(va_arg(arg,int));
                write(1,bin,mystrlen(bin));
            }
            else if ( format[i] == 'x' )//szesnastkowo
            {
                char *hex = dec2hex(va_arg(arg,int));
                write(1,hex,mystrlen(hex));
            }
        }

    }
    va_end(arg);
}

void myscanf(char *format, ...)
{
    va_list arg;
    va_start(arg,format);

    int length = mystrlen(format);
    int i;
    for(i = 0; i < length; ++i)
    {
        if( format[i] == '%')
        {
            ++i;
            if( format[i] == 's') // string
            {
                char *temp = (char*)malloc(sizeof(char) * BUFFERSIZE);
                read(0,temp,BUFFERSIZE);
                temp[mystrlen(temp) -1] = '{$content}';
                char **string = va_arg(arg,char*);
                *string = temp;

            }
            else if( format[i] == 'c')//char
            {
                char temp;
                read(0,&temp,1);
                char *c = (char*)va_arg(arg,int);
                *c = temp;
            }
            else if(format[i] == 'd')//int
            {

                char *temp = (char*)malloc(sizeof(char) * BUFFERSIZE);
                read(0,temp,BUFFERSIZE);
                temp[mystrlen(temp) - 1] = '{$content}';
                int *integer = va_arg(arg,int);
                *integer = string2int(temp);
            }
            else if( format[i] == 'b')//binarnie
            {
                char *temp = (char*)malloc(sizeof(char) * BUFFERSIZE);
                read(0,temp,BUFFERSIZE);
                temp[mystrlen(temp) - 1] = '{$content}';
                int *integer = va_arg(arg,int);
                *integer = bin2dec(temp);
            }
            else if( format[i] == 'x' ) //szesnastkowo
            {
                char *temp = (char*)malloc(sizeof(char) * BUFFERSIZE);
                read(0,temp,BUFFERSIZE);
                temp[mystrlen(temp) - 1] = '{$content}';
                int *integer = va_arg(arg,int);
                *integer = hex2dec(temp);
            }
        }
    }
    va_end(arg);
}

int main(int argc, char *argv[])
{

	int test=0;
myprintf("Miki");
return 0;
}
