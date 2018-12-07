`timescale 1ns / 1ns


module HLSM33 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, num, avg);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input signed [7:0] a;
	input signed [7:0] b;
	input signed [7:0] c;
	input signed [7:0] d;
	input signed [7:0] e;
	input signed [7:0] f;
	input signed [7:0] g;
	input signed [7:0] h;
	input signed [7:0] num;

	output reg signed [7:0] avg;

	reg signed [31:0] t1;
	reg signed [31:0] t2;
	reg signed [31:0] t3;
	reg signed [31:0] t4;
	reg signed [31:0] t5;
	reg signed [31:0] t6;
	reg signed [31:0] t7;



	always @(posedge Clk) begin
		if (Rst) begin
			avg <= 0; t1 <= 0; t2 <= 0; t3 <= 0; t4 <= 0; t5 <= 0; t6 <= 0; t7 <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					t1 <= a + b;
					State <= State + 1;
				end
				3 : begin
					t2 <= t1 + c;
					State <= State + 1;
				end
				4 : begin
					t3 <= t2 + d;
					State <= State + 1;
				end
				5 : begin
					t4 <= t3 + e;
					State <= State + 1;
				end
				6 : begin
					t5 <= t4 + f;
					State <= State + 1;
				end
				7 : begin
					t6 <= t5 + g;
					State <= State + 1;
				end
				8 : begin
					t7 <= t6 + h;
					State <= State + 1;
				end
				9 : begin
					avg <= t7 / num;
					State <= 1;
				end
			endcase
		end
	end
endmodule