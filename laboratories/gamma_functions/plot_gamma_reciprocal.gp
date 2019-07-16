
gnuplot

set termoption enhanced

set xzeroaxis
set yzeroaxis
set grid

set title "Reciprocal Gamma function 1/{/Symbol G}(x)"
set xlabel "x"
plot [-5.0:10.0][-20.0:5.0] \
                    "test_gamma_reciprocal_1.txt" index 0 using 1:2 with lines title "1/{/Symbol G}(x)"

set term push
set term png
set output "reciprocal_gamma.png"
replot
set term pop

set title "Reciprocal Gamma function 1/{/Symbol G}(x)"
set xlabel "x"
plot [-4.0:6.0][-2.0:5.0] \
                    "test_gamma_reciprocal.txt" index 0 using 1:2 with lines title "1/{/Symbol G}(x)"

set term push
set term png
set output "reciprocal_gamma_2.png"
replot
set term pop
