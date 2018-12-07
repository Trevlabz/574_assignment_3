`timescale 1ns / 1ns


module HLSM2 (Clk, Rst, Start, Done, a, b, c, d, e, i);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input signed [15:0] a;
	input signed [15:0] b;
	input signed [15:0] c;
	input signed [15:0] d;
	input signed [15:0] e;

	output reg signed [15:0] i;

	reg signed [15:0] f;
	reg signed [15:0] g;
	reg signed [15:0] h;



	always @(posedge Clk) begin
		if (Rst) begin
			i <= 0; f <= 0; g <= 0; h <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					f <= a * b;
					State <= State + 1;
				end
				3 : begin
					State <= State + 1;
				end
				4 : begin
					g <= f * c;
					State <= State + 1;
				end
				5 : begin
					State <= State + 1;
				end
				6 : begin
					h <= g * d;
					State <= State + 1;
				end
				7 : begin
					State <= State + 1;
				end
				8 : begin
					i <= h * e;
					State <= 1;
				end
			endcase
		end
	end
endmodule