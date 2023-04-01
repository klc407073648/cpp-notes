#read config file
config_file=go_config

log_path=`cat $config_file |grep "log_path=" |cut -f2 -d'='`
log_name=`cat $config_file |grep "log_name=" |cut -f2 -d'='`

echo "log_path=$log_path"
echo "log_name=$log_name"

cur_path=`pwd`

log_dir=$cur_path/$log_path
log_file=$log_dir/$log_name
GOPATH=$cur_path
print_all_log=1

echo "log_dir=$log_dir"
echo "log_file=$log_file"
echo "GOPATH=$GOPATH"

#write log func
function write_log()
{
  if [ ! -d ${log_dir} ];then
	 mkdir -p ${log_dir} 
  fi
  
  if [ ! -f ${log_file} ];then
	 touch  ${log_file} 
  fi
  
  fileCount=`ls ${log_dir}/*.log |wc -l`
  
  if [ ${fileCount} -gt 10 ];then
     find ${log_dir} -type f |xargs ls -tr | head -5 | xargs rm
  fi
  
  echo -n `date "+%Y-%m-%d %T "` >>${log_file}
  echo " $1" >>${log_file}
  
  return 0
}

#log print func defalut:print_all_log == 1
function logDebug()
{
   if [ $print_all_log == 1 ];then 
      echo -e "\033[32m-- $1 --\033[0m"  &&  write_log "-- $1 --"
   fi
}

function logInfo()
{
   if [ $print_all_log == 1 ];then 
      echo -e "\033[36m-- $1 --\033[0m"  &&  write_log "-- $1 --"
   fi
}

function logWarn()
{
   echo -e "\033[33m-- $1 --\033[0m"  &&  write_log "-- $1 --"
}

function logError()
{
   echo -e "\033[31m-- $1 --\033[0m"  &&  write_log "-- $1 --"
}

