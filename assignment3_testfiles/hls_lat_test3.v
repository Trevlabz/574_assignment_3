`timescale 1ns / 1ns


module HLSM3 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, i, j, k, l);

	input Clk, Rst, Start;
	output reg Done;
	reg [2:0] State;

	input signed [15:0] a;
	input signed [15:0] b;
	input signed [15:0] c;
	input signed [15:0] d;
	input signed [15:0] e;
	input signed [15:0] f;
	input signed [15:0] g;
	input signed [15:0] h;

	output reg signed [15:0] i;
	output reg signed [15:0] j;
	output reg signed [15:0] k;
	output reg signed [15:0] l;




	always @(posedge Clk) begin
		if (Rst) begin
			i <= 0; j <= 0; k <= 0; l <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					i <= a * b;
					j <= c * d;
					k <= e * f;
					l <= g * h;
					State <= 1;
				end
			endcase
		end
	end
endmodule