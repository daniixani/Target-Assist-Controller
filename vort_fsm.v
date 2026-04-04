`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/01/2026 05:29:37 PM
// Design Name: 
// Module Name: vort_fsm
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


module vort_fsm(

input clk,
input reset,
input A,
input T,
input L,
input F,
input R,

output reg AR, // armed indicator
output reg RDY, // ready
output reg X, //fault or locked mode
output reg FE,// trigger ready
output reg B // alignment signal (aim)
    );
    
    //states definition
 localparam IDLE = 2'b00;
 localparam SEARCH = 2'b01;
 localparam READY = 2'b10;
 localparam LOCKED = 2'b11;
 
 reg [1:0] current_state, next_state;
 //state reg
 always @(posedge clk or posedge reset) begin
 if (reset)
    current_state <= IDLE;
    else
    current_state <= next_state;
    end
 //next state steps
 always @(*) begin
 case (current_state)
 
    IDLE: begin
    if (F)
    next_state = LOCKED;
    else if (A)
    next_state = SEARCH;
    else
    next_state = IDLE;
    end
    
    SEARCH: begin
    if (F)
    next_state = LOCKED;
    else if (!A)
    next_state = IDLE;
    else if (T && L)
    next_state = READY;
    else
    next_state = SEARCH;
    end
    
    READY: begin
    if (F)
    next_state = LOCKED;
    else if (!A)
    next_state = IDLE;
    else if (!L || !T)
    next_state = SEARCH;
    else
    next_state = READY;
    end
    
    LOCKED: begin
    if (R && !F)
    next_state = IDLE;
    else
    next_state = LOCKED;
    end
    endcase
  end
  //using moore fsm for output
  always @(*) begin
    case (current_state)

        IDLE: begin
            AR  = 1'b0;
            RDY = 1'b0;
            X   = 1'b0;
            FE  = 1'b0;
            B   = 1'b0;
        end
        
        SEARCH: begin
            AR = 1'b1;
            RDY = 1'b0;
            X   = 1'b0;
            FE  = 1'b0;
            B   = 1'b0;
         end
         
         READY: begin
         AR = 1'b1;
         RDY = 1'b1;
         X   = 1'b0;
         FE  = 1'b1;
         B   = 1'b1;
       end
       
         LOCKED: begin
         AR = 1'b0;
         RDY = 1'b0;
         X   = 1'b1;
         FE  = 1'b0;
         B   = 1'b0;
       end
       
       default:begin
       AR = 1'b0;
       RDY = 1'b0;
       X   = 1'b0;
       FE  = 1'b0;
       B   = 1'b0;
     end
    endcase
  end
    
endmodule
