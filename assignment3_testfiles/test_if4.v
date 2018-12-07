`timescale 1ns / 1ns


module HLSM14 (Clk, Rst, Start, Done, a, b, c, zero, one, t, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [2:0] State;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	input signed [31:0] zero;
	input signed [31:0] one;
	input signed t;

	output reg signed [31:0] z;
	output reg signed [31:0] x;

	reg signed [31:0] e;
	reg signed [31:0] g;
	reg signed [31:0] d;
	reg signed [31:0] f;



	always @(posedge Clk) begin
		if (Rst) begin
			z <= 0; x <= 0; e <= 0; g <= 0; d <= 0; f <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					d <= a + b;
					if (!t) begin
					e <= a + c;
					f <= a * c;
					end
					State <= State + 1;
				end
				3 : begin
					if (t) begin
					d <= a - one;
					end
					State <= State + 1;
				end
				4 : begin
					if (t) begin
					f <= a + c;
					end else begin
					g <= d > e;
					end
					State <= State + 1;
				end
				5 : begin
					if (t) begin
					x <= f - d;
					end else begin
					z <= g ? d : e;
					x <= f - d;
					end
					State <= 1;
				end
			endcase
		end
	end
endmodule