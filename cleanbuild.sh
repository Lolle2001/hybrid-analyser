OPTION=$1

if [[ $OPTION -eq 0 ]]
then
rm -rf build
elif [[ $OPTION -eq 1 ]]
then 
rm -rf build-evo-ampt
elif [[ $OPTION -eq 2 ]]
then
rm -rf build-evo-music
fi