`timescale 1ns / 1ns


module HLSM31 (Clk, Rst, Start, Done, a, b, c, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [2:0] State;

	input [15:0] a;
	input [15:0] b;
	input [15:0] c;

	output reg [7:0] z;
	output reg [15:0] x;

	reg [7:0] d;
	reg [7:0] e;
	reg [7:0] f;
	reg [7:0] g;



	always @(posedge Clk) begin
		if (Rst) begin
			z <= 0; x <= 0; d <= 0; e <= 0; f <= 0; g <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					d <= a + b;
					f <= a * c;
					State <= State + 1;
				end
				3 : begin
					e <= a + c;
					State <= State + 1;
				end
				4 : begin
					g <= d > e;
					x <= f - d;
					State <= State + 1;
				end
				5 : begin
					z <= g ? d : e;
					State <= 1;
				end
			endcase
		end
	end
endmodule