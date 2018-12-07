`timescale 1ns / 1ns


module HLSM (Clk, Rst, Start, Done, a, b, c, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [2:0] State;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;

	output reg signed [31:0] z;
	output reg signed [31:0] x;

	reg signed [31:0] d;
	reg signed [31:0] f;
	reg signed [31:0] g;
	reg signed [31:0] zrin;



	always @(posedge Clk) begin
		if (Rst) begin
			z <= 0; x <= 0; d <= 0; f <= 0; g <= 0; zrin <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					d <= a + b;
					g <= a < b;
					f <= a * c;
					State <= State + 1;
				end
				3 : begin
					zrin <= a + c;
					State <= State + 1;
				end
				4 : begin
					if (g) begin
					zrin <= a + b;
					end
					State <= State + 1;
				end
				5 : begin
					x <= f - d;
					z <= zrin + f;
					State <= 1;
				end
			endcase
		end
	end
endmodule