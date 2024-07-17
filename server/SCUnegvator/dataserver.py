import socket,sqlite3,psycopg2,threading,time

socket_server=socket.socket(socket.AF_INET, socket.SOCK_STREAM )
socket_server.bind(("0.0.0.0",9998))
socket_server.listen(50)
client_container=list()
thread=list()

def iterToStr(a):
    b=[]
    for j in a:
        a=list(str(i) for i in j)
        b.append(a)
    a=b
    b=[]
    for i in a:
        c='@sql@'.join(i)
        b.append(c)
    b='\n'.join(b)
    return b

def check_connection(connection):#检查连接是否断开
    try:
        connection.settimeout(0.2)
        connection.send(b'')
        connection.settimeout(None)
        return True
    except connection.timeout:
        return False

def getData(conn):
    if(check_connection(conn)==False):#检查连接是否断开
            client_container.remove(conn)
            conn.close()
            print('Client is disconnected...')
            return
    while True:
        try:
            data :str= conn.recv(1024).decode("utf-8")#接收客户端消息
        except conn.timeout :#如果客户端断开连接
            client_container.remove(conn)
            with open("./datalog.log",'a+') as f:
                f.write(f'Client is disconnected...'+time.ctime()+'\n')
            conn.close()
            return
        #进程判断
        if(data=="EXITNOWTIME"):
            client_container.remove(conn)
            with open("./data.log",'a+') as f:
                f.write(f'{id} of Client is disconnected...'+time.ctime()+'\n')
            conn.close()
            return


        with open("./data.log",'a+') as f:
                f.write(data+time.ctime()+'\n')
        '''
        if not data:
            client_container.remove(conn)
            conn.close()
            return
        '''
        #table= data.split("from",1)[1].strip()
        con=psycopg2.connect(database='scunegvator_db',user='aboy',password='aboy',host='127.0.0.1')
        
        with con:
            cur=con.cursor()
            cur.execute(data)
            data=data.strip()
            CMD=data.split(' ')[0]
            if(CMD=="SELECT" or CMD=="select"):
                arr=cur.fetchall()
                #print(arr)
                with open("./data.log",'a+') as f:
                    f.write(iterToStr(arr)+time.ctime()+"\n")
                conn.send(iterToStr(arr).encode('utf-8'))
            else:
                if(cur.rowcount!=0):
                    with open("./data.log",'a+') as f:
                        f.write(f"{CMD} success"+time.ctime()+"\n")
                    conn.send("SUC".encode('utf-8'))
                else:
                    with open("./data.log",'a+') as f:
                        f.write(f"{CMD} erro"+time.ctime()+"\n")
                    conn.send("ERRO".encode('utf-8'))
            
       
            

while True:
    connection,client_address=socket_server.accept()
    with open("./data.log",'a+') as f:
        f.write(f"Connected by {client_address}"+time.ctime()+'\n')
    client_container.append(connection)
    thread.append(threading.Thread(target=getData,args=[connection]))
    thread[len(thread)-1].start()
    for i in thread:
            if((i.is_alive())==False):
                thread.remove(i)