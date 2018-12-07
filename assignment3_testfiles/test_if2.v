`timescale 1ns / 1ns


module HLSM2 (Clk, Rst, Start, Done, a, b, c, one, z, x);

	input Clk, Rst, Start;
	output reg Done;
	reg [3:0] State;

	input signed [31:0] a;
	input signed [31:0] b;
	input signed [31:0] c;
	input signed [31:0] one;

	output reg signed [31:0] z;
	output reg signed [31:0] x;

	reg signed [31:0] d;
	reg signed [31:0] e;
	reg signed [31:0] f;
	reg signed [31:0] g;
	reg signed [31:0] h;
	reg signed dLTe;
	reg signed dEQe;
	reg signed dLTEe;



	always @(posedge Clk) begin
		if (Rst) begin
			z <= 0; x <= 0; d <= 0; e <= 0; f <= 0; g <= 0; h <= 0; dLTe <= 0; dEQe <= 0; dLTEe <= 0; 
			State <= 0; Done <= 0;
		end
		else begin
			case (State)
				0 : begin if (Start) State <= 2; end
				1 : begin Done <= 1; State <= 0; end
				2 : begin
					f <= a - b;
					State <= State + 1;
				end
				3 : begin
					d <= a + b;
					e <= a + c;
					State <= State + 1;
				end
				4 : begin
					dEQe <= d == e;
					State <= State + 1;
				end
				5 : begin
					dLTEe <= dEQe + dLTe;
					State <= State + 1;
				end
				6 : begin
					dLTe <= d > e;
					if (dLTEe) begin
					g <= d + e;
					end
					z <= h >> one;
					State <= State + 1;
				end
				7 : begin
					if (dLTEe) begin
					if (dLTe) begin
					h <= f + one;
					end
					end
					State <= State + 1;
				end
				8 : begin
					if (dLTEe) begin
					h <= f + e;
					end
					State <= State + 1;
				end
				9 : begin
					if (dLTEe) begin
					if (dLTe) begin
					g <= e + one;
					end
					end
					x <= h << one;
					State <= 1;
				end
			endcase
		end
	end
endmodule