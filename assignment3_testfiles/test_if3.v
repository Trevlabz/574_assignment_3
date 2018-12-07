`timescale 1ns / 1ns


module HLSM3 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, sa, one, two, four, avg);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	input signed [31:0] d;
	input signed [31:0] e;
	input signed [31:0] f;
	input signed [31:0] g;
	input signed [31:0] h;
	input signed [31:0] sa;
	input signed [31:0] one;
	input signed [31:0] two;
	input signed [31:0] four;

	output reg signed [31:0] avg;

	reg signed [31:0] t1;
	reg signed [31:0] t2;
	reg signed [31:0] t3;
	reg signed [31:0] t4;
	reg signed [31:0] t5;
	reg signed [31:0] t6;
	reg signed [31:0] t7;
	reg signed [31:0] t7div2;
	reg signed [31:0] t7div4;
	reg signed csa1;
	reg signed csa2;
	reg signed csa3;



	always @(posedge Clk) begin
		if (Rst) begin
			avg <= 0; t1 <= 0; t2 <= 0; t3 <= 0; t4 <= 0; t5 <= 0; t6 <= 0; t7 <= 0; t7div2 <= 0; t7div4 <= 0; csa1 <= 0; csa2 <= 0; csa3 <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					t1 <= a + b;
					csa2 <= sa > two;
					State <= State + 1;
				end
				3 : begin
					t2 <= t1 + c;
					csa3 <= sa > four;
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
					csa1 <= sa > one;
					State <= State + 1;
				end
				9 : begin
					if (csa1) begin
					t7div2 <= t7 >> one;
					end
					State <= State + 1;
				end
				10 : begin
					if (csa1) begin
					if (csa2) begin
					t7div4 <= t7div2 >> one;
					end
					if (!csa2) begin
					t7div4 <= t7 >> one;
					end
					end
					State <= State + 1;
				end
				11 : begin
					if (csa1) begin
					if (!csa2) begin
					if (csa3) begin
					avg <= t7div4 >> one;
					end
					end
					end
					State <= 1;
				end
			endcase
		end
	end
endmodule