`timescale 1ns / 1ns


module HLSM37 (Clk, Rst, Start, Done, u, x, y, dx, a, three, u1, x1, y1, c);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input signed [31:0] u;
	input signed [31:0] x;
	input signed [31:0] y;
	input signed [31:0] dx;
	input signed [31:0] a;
	input signed [31:0] three;

	output reg signed [31:0] u1;
	output reg signed [31:0] x1;
	output reg signed [31:0] y1;
	output reg signed [31:0] c;

	reg signed [31:0] t1;
	reg signed [31:0] t2;
	reg signed [31:0] t3;
	reg signed [31:0] t4;
	reg signed [31:0] t5;
	reg signed [31:0] t6;
	reg signed [31:0] t7;
	reg signed [31:0] vx1;



	always @(posedge Clk) begin
		if (Rst) begin
			u1 <= 0; x1 <= 0; y1 <= 0; c <= 0; t1 <= 0; t2 <= 0; t3 <= 0; t4 <= 0; t5 <= 0; t6 <= 0; t7 <= 0; vx1 <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					vx1 <= x + dx;
					t1 <= three * x;
					State <= State + 1;
				end
				3 : begin
					t2 <= u * dx;
					State <= State + 1;
				end
				4 : begin
					t5 <= three * y;
					State <= State + 1;
				end
				5 : begin
					x1 <= x + dx;
					t7 <= u * dx;
					State <= State + 1;
				end
				6 : begin
					t3 <= t1 * t2;
					State <= State + 1;
				end
				7 : begin
					t4 <= u - t3;
					t6 <= t5 * dx;
					State <= State + 1;
				end
				8 : begin
					u1 <= t4 - t6;
					c <= vx1 < a;
					State <= State + 1;
				end
				9 : begin
					y1 <= y + t7;
					State <= 1;
				end
			endcase
		end
	end
endmodule