create_clock -name clk -period 10 {}
set_input_delay -clock clk 0 {
a[9]
a[8]
a[7]
a[6]
a[5]
a[4]
a[3]
a[2]
a[23]
a[22]
a[21]
a[20]
a[1]
a[19]
a[18]
a[17]
a[16]
a[15]
a[14]
a[13]
a[12]
a[11]
a[10]
a[0]
}
set_output_delay -clock clk 0 {
sin[9]
sin[8]
sin[7]
sin[6]
sin[5]
sin[4]
sin[3]
sin[2]
sin[24]
sin[23]
sin[22]
sin[21]
sin[20]
sin[1]
sin[19]
sin[18]
sin[17]
sin[16]
sin[15]
sin[14]
sin[13]
sin[12]
sin[11]
sin[10]
sin[0]
}