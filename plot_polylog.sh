
gnuplot

set termoption enhanced

set xzeroaxis
set yzeroaxis
set grid

set title "Polylog Li_{4.1}(x)"
set xlabel "x"
set polar
plot [-0.1:6.3][-4.0:4.0] \
                    "debug_polylog.txt" index 0 using 1:2 with lines title "Re[Li_{4.1}(x)]", \
                    "" index 0 using 1:3 with lines title "Im[Li_{4.1}(x)]", \
                    "" index 0 using 1:4 with lines title "Re[Li_{4.1}(x)]", \
                    "" index 0 using 1:5 with lines title "Im[Li_{4.1}(x)]", \
                    "" index 0 using 1:6 with lines title "Li_{4.1}(x)"

unset polar

set title "Polylog Li_{s}(x)"
set xlabel "x"
plot [-20.0:1.0][-10.0:10.0] \
                    "test_polylog.txt" index 0 using 1:3 with lines title "Li_{0}(x)", \
                    "" index 1 using 1:2 with lines title "Li_{1}(x)", \
                    "" index 2 using 1:3 with lines title "Li_{2}(x)", \
                    "" index 6 using 2:4 with lines title "Li_{3}(x)", \
                    "" index 7 using 2:4 with lines title "Li_{4}(x)", \
                    "" index 8 using 2:4 with lines title "Li_{5}(x)", \
                    "" index 9 using 2:6 with lines title "Li_{-1}(x)", \
                    "" index 10 using 2:6 with lines title "Li_{-2}(x)", \
                    "" index 11 using 2:6 with lines title "Li_{-3}(x)"

set title "Polylog Li_{0}(x)"
set xlabel "x"
plot [-20.0:1.0][-1.0:10.0] \
                    "test_polylog.txt" index 0 using 1:2 with lines title "Li_{0}(x)", \
                    "" index 0 using 1:3 with lines title "Li_{0}(x)"

set title "Polylog Li_{1}(x)"
set xlabel "x"
plot [-20.0:1.0][-3.5:2.5] \
                    "test_polylog.txt" index 1 using 1:2 with lines title "Li_{1}(x)", \
                    "" index 1 using 1:3 with lines title "Li_{1}(x)"

set title "Polylog Li_{2}(x)"
set xlabel "x"
plot [-20.0:1.0][-6.5:2.0] \
                    "test_polylog.txt" index 2 using 1:2 with lines title "Li_{2}(x)", \
                    "" index 2 using 1:3 with lines title "Li_{2}(x)"


set title "Polylog Li_{0}(x) vs Cephes"
set xlabel "x"
plot [-20.0:1.0][-1.0:10.0] \
                    "test_polylog.txt" index 3 using 2:3 with lines title "Li_{0}(x)", \
                    "" index 3 using 2:4 with lines title "Li_{0}(x)"

set title "Polylog Li_{1}(x) vs Cephes"
set xlabel "x"
plot [-20.0:1.0][-3.5:2.5] \
                    "test_polylog.txt" index 4 using 2:3 with lines title "Li_{1}(x)", \
                    "" index 4 using 2:4 with lines title "Li_{1}(x)"

set title "Polylog Li_{2}(x) vs Cephes"
set xlabel "x"
plot [-20.0:1.0][-6.5:2.0] \
                    "test_polylog.txt" index 5 using 2:3 with lines title "Li_{2}(x)", \
                    "" index 5 using 2:4 with lines title "Li_{2}(x)"

set title "Polylog Li_{3}(x) vs Cephes"
set xlabel "x"
plot [-20.0:1.0][-10.0:1.5] \
                    "test_polylog.txt" index 6 using 2:3 with lines title "Li_{3}(x)", \
                    "" index 6 using 2:4 with lines title "Li_{3}(x)"

set title "Polylog Li_{4}(x) vs Cephes"
set xlabel "x"
plot [-20.0:1.0][-13.0:1.2] \
                    "test_polylog.txt" index 7 using 2:3 with lines title "Li_{4}(x)", \
                    "" index 7 using 2:4 with lines title "Li_{4}(x)"

set title "Polylog Li_{5}(x) vs Cephes"
set xlabel "x"
plot [-20.0:1.0][-15.5:1.1] \
                    "test_polylog.txt" index 8 using 2:3 with lines title "Li_{5}(x)", \
                    "" index 8 using 2:4 with lines title "Li_{5}(x)"

set title "Polylog Li_{-1}(x)"
set xlabel "x"
plot [-10.0:1.0][-1.0:1.0] \
                    "test_polylog.txt" index 9 using 2:3 with lines title "Li_{-1}(x)", \
                    "" index 9 using 2:4 with lines title "Li_{-1}(x)", \
                    "" index 9 using 2:5 with lines title "Li_{-1}(x)", \
                    "" index 9 using 2:6 with lines title "Li_{-1}(x)", \
                    "" index 9 using 2:7 with lines title "Li_{-1}(x)"

set title "Polylog Li_{-2}(x)"
set xlabel "x"
plot [-10.0:1.0][-1.0:1.0] \
                    "test_polylog.txt" index 10 using 2:3 with lines title "Li_{-2}(x)", \
                    "" index 10 using 2:4 with lines title "Li_{-2}(x)", \
                    "" index 10 using 2:5 with lines title "Li_{-2}(x)", \
                    "" index 10 using 2:6 with lines title "Li_{-2}(x)", \
                    "" index 10 using 2:7 with lines title "Li_{-2}(x)"

set title "Polylog Li_{-3}(x)"
set xlabel "x"
plot [-10.0:1.0][-1.0:1.0] \
                    "test_polylog.txt" index 11 using 2:3 with lines title "Li_{-3}(x)", \
                    "" index 11 using 2:4 with lines title "Li_{-3}(x)", \
                    "" index 11 using 2:5 with lines title "Li_{-3}(x)", \
                    "" index 11 using 2:6 with lines title "Li_{-3}(x)", \
                    "" index 11 using 2:7 with lines title "Li_{-3}(x)"

set title "Polylog Li_{-4}(x)"
set xlabel "x"
plot [-10.0:1.0][-1.0:1.0] \
                    "test_polylog.txt" index 12 using 2:3 with lines title "Li_{-4}(x)", \
                    "" index 12 using 2:4 with lines title "Li_{-4}(x)", \
                    "" index 12 using 2:5 with lines title "Li_{-4}(x)", \
                    "" index 12 using 2:6 with lines title "Li_{-4}(x)", \
                    "" index 12 using 2:7 with lines title "Li_{-4}(x)"

set title "Polylog Li_{-5}(x)"
set xlabel "x"
plot [-10.0:1.0][-1.0:1.0] \
                    "test_polylog.txt" index 13 using 2:3 with lines title "Li_{-5}(x)", \
                    "" index 13 using 2:4 with lines title "Li_{-5}(x)", \
                    "" index 13 using 2:5 with lines title "Li_{-5}(x)", \
                    "" index 13 using 2:6 with lines title "Li_{-5}(x)", \
                    "" index 13 using 2:7 with lines title "Li_{-5}(x)"
