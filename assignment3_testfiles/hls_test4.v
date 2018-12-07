`timescale 1ns / 1ns


module HLSM34 (Clk, Rst, Start, Done, a, b, c, d, zero, z);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input [63:0] a;
	input [63:0] b;
	input [63:0] c;
	input [63:0] d;
	input [63:0] zero;

	output reg [63:0] z;

	reg [63:0] e;
	reg [63:0] f;
	reg [63:0] g;
	reg gEQz;



	always @(posedge Clk) begin
		if (Rst) begin
			z <= 0; e <= 0; f <= 0; g <= 0; gEQz <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					f <= c / d;
					State <= State + 1;
				end
				3 : begin
					State <= State + 1;
				end
				4 : begin
					State <= State + 1;
				end
				5 : begin
					g <= a % b;
					State <= State + 1;
				end
				6 : begin
					e <= a / b;
					gEQz <= g == zero;
					State <= State + 1;
				end
				7 : begin
					z <= gEQz ? e : f;
					State <= 1;
				end
			endcase
		end
	end
endmodule