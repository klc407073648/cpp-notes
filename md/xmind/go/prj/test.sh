config_file=go_config

source ./common.sh

cur_path=`pwd`
export GOPATH=$cur_path

echo "GOPATH=$GOPATH"

function parseConfigFile()
{
   logInfo "parseConfigFile begin"

   logDebug "parse var from $config_file"

   build_list=`cat $config_file |grep "build_list=" |cut -f2 -d'='`

   logDebug "build_list is $build_list"

   logInfo "parseConfigFile end"
}

function buildGoProject()
{
   logInfo "buildGoProject begin"
   
   for build_name in $build_list  
   do
      cd $GOPATH/src/$build_name

      logInfo "begin to build src/$build_name"

      for go_project in `ls`  
      do   
         logDebug "$go_project begin"
         go run $go_project
         logDebug "$go_project end"
      done
 
      logInfo "end to build src/$build_name"
   done

   logInfo "buildGoProject end" 
}

function MAIN()
{
   logInfo "MAIN begin"
   parseConfigFile
   buildGoProject
   logInfo "MAIN end" 
}

MAIN