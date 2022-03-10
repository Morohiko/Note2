SCRIPTPATH="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P)"
ROOTPATH=$(echo $SCRIPTPATH | awk 'BEGIN{FS=OFS="/"} NF--')

cleanup_and_exit() {
  if [ -d $BUILDDIRPATH ]; then
    rm -rf $BUILDDIRPATH
  fi
  exit
}

############# make build directory
BUILDDIRPATH=$ROOTPATH"/build_dir_ci"
if [ -d $BUILDDIRPATH ]; then
  rm -rf $BUILDDIRPATH
fi
mkdir $BUILDDIRPATH
if [ ! -d $BUILDDIRPATH ]; then
  echo build dir path is not created $BUILDDIRPATH
  exit
fi

############ build dummy tests
echo building..
cd $BUILDDIRPATH
cmake .. -DPLATFORM=dummy -DWITH_TESTS=on > /dev/null
if [ $? != 0 ]; then
  echo error on cmake $?
  exit
fi
make -j8 > /dev/null
if [ $? != 0 ]; then
  echo error on make $?
  exit
fi

########### run dummy tests
cd $BUILDDIRPATH
echo run file_test
$BUILDDIRPATH"/file_test" > /dev/null
echo file test status: $?

echo run datetime_test
$BUILDDIRPATH"/datetime_test" > /dev/null
echo datetime test status: $?

echo run parser_test
$BUILDDIRPATH"/parser_test" > /dev/null
echo parser test status: $?

echo run dummy_test
$BUILDDIRPATH"/dummy_test" > /dev/null
echo dummy test status: $?

cleanup_and_exit
