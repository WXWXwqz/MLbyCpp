#bash
qmake -project
qmake
qmake
make
./MLPDoubleMoon
make clean
gnuplot -persist <<EOF
plot "moon1.txt","moon2.txt"