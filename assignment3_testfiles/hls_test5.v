`timescale 1ns / 1ns


module HLSM35 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, sa, avg);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input [31:0] a;
	input [31:0] b;
	input [31:0] c;
	input [31:0] d;
	input [31:0] e;
	input [31:0] f;
	input [31:0] g;
	input [31:0] h;
	input [31:0] sa;

	output reg [31:0] avg;

	reg [31:0] t1;
	reg [31:0] t2;
	reg [31:0] t3;
	reg [31:0] t4;
	reg [31:0] t5;
	reg [31:0] t6;
	reg [31:0] t7;
	reg [31:0] t7div2;
	reg [31:0] t7div4;



	always @(posedge Clk) begin
		if (Rst) begin
			avg <= 0; t1 <= 0; t2 <= 0; t3 <= 0; t4 <= 0; t5 <= 0; t6 <= 0; t7 <= 0; t7div2 <= 0; t7div4 <= 0; 
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
					t7div2 <= t7 >> sa;
					State <= State + 1;
				end
				10 : begin
					t7div4 <= t7div2 >> sa;
					State <= State + 1;
				end
				11 : begin
					avg <= t7div4 >> sa;
					State <= 1;
				end
			endcase
		end
	end
endmodule