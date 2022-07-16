
size_t size;
void *p;

p = (void *)packet->src_address;
size = strlen(packet->src_address) + 1;
memcpy(buf, p, size);
buf += size;

p = (void *)packet->dest_address;
size = strlen(packet->dest_address) + 1;
memcpy(buf, p, size);
buf += size;

p = (void *)&packet->user_type;
size = sizeof(packet->usertype)
memcpy(buf, p, size);
buf += size;


定义宏消除

#define APPEND_TO_BUF(content,size) do{\ 
  memcpy(buf(void*)content,size);\ 
  buf+=size; \
} while(0)

APPEND_TO_BUF(packet->src_address,strlen(packet->src address)+1) 
APPEND_TO_BUF(packet->src_address,strlen(packet->src_address)+1); 
APPEND_TO_BUF(packet->user_type,sizeof(packet->user_type));

进一步消除


#define APPEND_STR_TO_BUF(str) APPEND_TO_BUF((str),strlen(str)+1)
#define APPEND_DATA_TO_BUF(data) APPEND_TO_BUF((data),sizeof(data))
///// ///////////// 
APPEND_STR_TO_BUF(packet->src_address);
APPEND_STR_TO_BUF(packet->src_address); 
APPEND_DATA_TO_BUF(packet->user_type);