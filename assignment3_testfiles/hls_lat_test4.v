`timescale 1ns / 1ns


module HLSM4 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, j, l);

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

	output reg signed [15:0] j;
	output reg signed [15:0] l;

	reg signed [15:0] h;
	reg signed [15:0] i;
	reg signed [15:0] k;



	always @(posedge Clk) begin
		if (Rst) begin
			j <= 0; l <= 0; h <= 0; i <= 0; k <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					h <= a + b;
					k <= e * f;
					State <= State + 1;
				end
				3 : begin
					i <= h + c;
					State <= State + 1;
				end
				4 : begin
					j <= i + d;
					l <= k * g;
					State <= 1;
				end
			endcase
		end
	end
endmodule