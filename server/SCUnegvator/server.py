import socket,threading,time,psycopg2

socket_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_server.bind(('0.0.0.0', 9999))
socket_server.listen(50)#一次最多50个连接
thread=list()
client_container=list()
client_container=list() #客户端连接容器
id_check=dict()
#socket_server.settimeout
with open('./log.log','a+') as f:
    f.write('Server is running...,waiting for the client connection...\n')


def check_connection(connection):#检查连接是否断开
    try:
        connection.settimeout(0.2)
        connection.send(b'')
        connection.settimeout(None)
        return True
    except connection.timeout:
        return False

def chatting(conn):
    isRoot=False
    
    id='default'
    #mybuf=list()
    print('chatting...')
    while True: #循环接收客户端消息

        if(check_connection(conn)==False):#检查连接是否断开
            client_container.remove(conn)
            conn.close()
            with open("./log.log",'a+') as f:
                f.write(f'{id} of Client is disconnected...'+time.ctime()+'\n')
            return
        #nowTime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        nowTime=time.ctime()
        
        try:
            datas :str= conn.recv(1024).decode("utf-8")#接收客户端消息
        except conn.timeout :#如果客户端断开连接
            client_container.remove(conn)
            with open("./log.log",'a+') as f:
                f.write(f'{id} of Client is disconnected...'+time.ctime()+'\n')
            conn.close()
            return
        #进程判断
        if(datas=="EXITNOWTIME"):
            client_container.remove(conn)
            with open("./log.log",'a+') as f:
                f.write(f'{id} of Client is disconnected...'+time.ctime()+'\n')
            conn.close()
            return

        #获取id
        id=datas.split(':',1)[0]
        print(id)
        conDb=psycopg2.connect(database='scunegvator_db',user='aboy',password='aboy',host='127.0.0.1')
        with conDb:
            cur=conDb.cursor()
            cur.execute(f"SELECT isroot from users where account = {id}")
            arr=cur.fetchone()
            if(arr[0]==True):
                isRoot=True
            else:
                isRoot=False

        if conn not in id_check:#id是否和conn绑定
            id_check.update({conn:id})
        

        
        data=(datas.split(':',1)[1]).strip()

        #检测是否为通用命令
        if(data=='/exit'):
                client_container.remove(conn)
                conn.close()
                with open("./log.log",'a+') as f:
                    f.write(f'{id} of Client is disconnected... /exit'+time.ctime()+'\n')
                continue
        elif(data=='/cls'):
            conn.send('CLSOKNOWTIME'.encode('utf-8'))
            with open("./log.log",'a+') as f:
                f.write(f'{id} of Client /cls'+time.ctime()+'\n')
            continue
            
        #检测是否为root命令
        
        if(data and data[0]=='/'):        
            CMD=data.split('/',1)[1]
            command=CMD.split('$',1)[0]
            if(command=='remove'): #remove 命令
                if(isRoot==False):
                    conn.send('Permission denied'.encode('utf-8'))
                    with open("./log.log",'a+') as f:
                        f.write(f'{id} of Client\'s Permission denied'+time.ctime()+'\n')

                    continue
                else:
                    if('$' in CMD):
                        arg=CMD.split('$')
                        for userId in arg:
                            userId=userId.strip()
                            for c in client_container:
                                if id_check[c]==userId:
                                    client_container.remove(c)
                                    c.close()
                                    for user in client_container:
                                        user.send(f'{userId} has be moved... '.encode('utf-8'))
                                    with open("./log.log",'a+') as f:
                                        f.write(f'{userId} has be moved... '+time.ctime()+'\n')    
                                        #服务器数据库加入该用户id状态为canJoin false=0,canChat false=0
                                    #print(f'Client is disconnected...: {userId}')
                                    #conn.send(f'Client is disconnected...: {userId}'.encode('utf-8'))
                                    continue

                    else:
                        arg=''
                        conn.send('/remove arg error'.encode('utf-8'))
                        with open("./log.log",'a+') as f:
                                f.write(f'{id} /remove arg error'+time.ctime()+'\n')    
                        continue
            elif(command=='clsAll'):#command clsAll
                if(isRoot==False):
                    conn.send('Permission denied'.encode('utf-8'))
                    with open("./log.log",'a+') as f:
                        f.write(f'{id} of Client\'s Permission denied'+time.ctime()+'\n')
                    continue
                else:
                    for c in client_container:
                        c.send('CLSOKNOWTIME'.encode('utf-8'))
                    with open("./log.log",'a+') as f:
                        f.write('clsALL'+time.ctime()+'\n')

                    continue
            elif(command=='forbid'):#command forbid
                if(isRoot==False):
                    conn.send('Permission denied'.encode('utf-8'))
                    with open("./log.log",'a+') as f:
                        f.write(f'{id} of Client\'s Permission denied'+time.ctime()+'\n')
                    continue
                else:
                    if('$' in CMD):
                        arg=CMD.split('$')
                        for userId in arg:
                            userId=userId.strip()
                            for c in client_container:
                                if id_check[c]==userId:
                                    c.send('FORBIDOKNOWTIME'.encode('utf-8'))
                                    #服务器数据库加入该用户id状态为canJoin false=1,canChat false=0
                                for user in client_container:
                                    user.send(f'{userId} has been forbid... '.encode('utf-8'))
                                with open("./log.log",'a+') as f:
                                    f.write(f'{userId} has been forbid... '+time.ctime()+'\n')
                                continue

                    else:
                        arg=''
                        conn.send('/forbid arg error'.encode('utf-8'))
                        with open("./log.log",'a+') as f:
                            f.write(f'{id} of Client\'s /forbid arg erro'+time.ctime()+'\n')
                        continue
            elif(command=='allow'):#command allow
                if(isRoot==False):
                    conn.send('Permission denied'.encode('utf-8'))
                    with open("./log.log",'a+') as f:
                        f.write(f'{id} of Client\'s Permission denied'+time.ctime()+'\n')
                    continue
                else:
                    if('$' in CMD):
                        arg=CMD.split('$')
                        for userId in arg:
                            userId=userId.strip()
                            for c in client_container:
                                if id_check[c]==userId:
                                    c.send('ALLOWOKNOWTIME'.encode('utf-8'))
                                for user in client_container:
                                    user.send(f'{userId} has been allowed... '.encode('utf-8'))
                                with open("./log.log",'a+') as f:
                                    f.write(f'{userId} has been allowed... '+time.ctime()+'\n')
                                continue

                    else:
                        arg=''
                        conn.send('/allow arg error'.encode('utf-8'))
                        with open("./log.log",'a+') as f:
                            f.write(f'{id} /allow arg error '+time.ctime()+'\n')
                        continue
            elif(command=='notice'):
                if(isRoot==False):
                    conn.send('/notice Permission denied'.encode('utf-8'))
                    with open("./log.log",'a+') as f:
                        f.write(f'{id} of Client\'s Permission denied'+time.ctime()+'\n')
                    continue
                else:
                    if('$' in CMD):
                        arg=CMD.split('$')[1]
                        if('$' in arg):
                            arg=''
                            conn.send('/notice arg error'.encode('utf-8'))
                            with open("./log.log",'a+') as f:
                                f.write(f'{id} /notice arg error '+time.ctime()+'\n')
                            continue  
                        else:
                            for c in client_container:
                                c.send(F"CHANGENOTICEOKNOWTIME@@{arg}".encode('utf-8'))
                            with open("./log.log",'a+') as f:
                                f.write(f'nitice has been changed to {arg} '+time.ctime()+'\n')
                            continue
            elif(command=='quit'):
                if(isRoot==False):
                        conn.send('Permission denied'.encode('utf-8'))
                        with open("./log.log",'a+') as f:
                            f.write(f'{id} of Client\'s Permission denied'+time.ctime()+'\n')

                        continue
                else:
                    if('$' in CMD):
                        arg=CMD.split('$')
                        for userId in arg:
                            userId=userId.strip()
                            for c in client_container:
                                if id_check[c]==userId:
                                    c.send("QUITOKNOWTIME".encode("utf-8"))
                                    client_container.remove(c)
                                    c.close()
                                    for user in client_container:
                                        user.send(f'{userId}\'exe has be quited... '.encode('utf-8'))
                                    with open("./log.log",'a+') as f:
                                        f.write(f'{userId}\'exe has be quited...'+time.ctime()+'\n')    
                                        #服务器数据库加入该用户id状态为canJoin false=0,canChat false=0
                                    #print(f'Client is disconnected...: {userId}')
                                    #conn.send(f'Client is disconnected...: {userId}'.encode('utf-8'))
                                    continue
                    else:
                        arg=''
                        conn.send('/quit arg error'.encode('utf-8'))
                        with open("./log.log",'a+') as f:
                                f.write(f'{id} /quit arg error'+time.ctime()+'\n')    
                        continue

        #消息数据
        datas ="用户 "+datas + f'  time: {nowTime}'
        with open("./log.log",'a+') as f:
            f.write(datas+'\n')
        for c in client_container:#将消息广播给所有客户端
            #if(c!=conn):
            c.send(datas.encode('utf-8'))
        
        
        
    



def main():
    # 主线程循环，接收并处理客户端连接
    while True:
        conct,socket_client=socket_server.accept()
        with open("./log.log",'a+') as f:
                f.write(f'Client is connected...: {socket_client}'+time.ctime()+'\n')
        client_container.append(conct)
        thread.append(threading.Thread(target=chatting,args=[conct])) #每个客户端连接都开一个线程，单独处理
        thread[len(thread)-1].start()
        for i in thread:
            if((i.is_alive())==False):
                thread.remove(i)
    # 循环处理多个客户端连接



main()

        