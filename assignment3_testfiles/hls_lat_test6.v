`timescale 1ns / 1ns


module HLSM6 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, k, l);

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

	output reg signed [15:0] k;
	output reg signed [15:0] l;

	reg signed [15:0] h;
	reg signed [15:0] i;
	reg signed [15:0] j;



	always @(posedge Clk) begin
		if (Rst) begin
			k <= 0; l <= 0; h <= 0; i <= 0; j <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					h <= a * b;
					i <= c * d;
					l <= f / g;
					State <= State + 1;
				end
				3 : begin
					State <= State + 1;
				end
				4 : begin
					j <= h + i;
					State <= State + 1;
				end
				5 : begin
					k <= j / e;
					State <= 1;
				end
			endcase
		end
	end
endmodule