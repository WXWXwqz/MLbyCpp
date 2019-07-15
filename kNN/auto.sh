#bash
qmake -project
qmake
qmake
make
./kNN
make clean
gnuplot -persist <<EOF
plot "moon1.txt","moon2.txt","tstmoon1.txt","tstmoon2.txt","board.txt"