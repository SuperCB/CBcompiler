with open('token.txt') as f:
    data = f.read().splitlines()  # 不读取换行符的做法

with open('result.txt','w') as res:
    for item in data:
        content = '''
'{token}'   {{    
             #ifdef DEBUG
              printf("%s\\n",yytext);
             #endif
     
             }} 
    '''
        token, type = item.split(' ')[0], item.split(' ')[-1]
        content = content.format(
            token=token,
            type=type
        )
        res.write(content)
