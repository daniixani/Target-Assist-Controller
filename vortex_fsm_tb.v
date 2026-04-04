`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/01/2026 06:05:11 PM
// Design Name: 
// Module Name: vortex_fsm_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module vortex_fsm_tb;

reg clk;
reg reset;
reg A;
reg T;
reg L;
reg F;
reg R;

wire AR;
wire RDY;
wire X;
wire FE;
wire B;

vort_fsm uut (
.clk(clk),
.reset(reset),
.A(A),
.T(T),
.L(L),
.F(F),
.R(R),
.AR(AR),
.RDY(RDY),
.X(X),
.FE(FE),
.B(B)

);

//clock
always #5 clk = ~clk;

initial begin
    clk   = 0;
    reset = 1;
    A     = 0;
    T     = 0;
    L     = 0;
    F     = 0;
    R     = 0;
    // reset to IDLE
#10 reset = 0;

// IDLE -> SEARCHING
A = 1; T = 0; L = 0; F = 0; R = 0;
#10;

// SEARCHING -> READY
T = 1; L = 1;
#10;

// READY -> SEARCHING (alignment lost)
L = 0;
#10;

// SEARCHING -> READY again
L = 1;
#10;

// READY -> LOCKOUT (fault)
F = 1;
#10;

// stay LOCKOUT even if fault clears
F = 0; R = 0;
#10;

// LOCKOUT -> IDLE with reset command
R = 1;
#10;
R = 0;

// IDLE stays IDLE if not armed
A = 0; T = 0; L = 0; F = 0;
#10;

$finish;
end
endmodule
