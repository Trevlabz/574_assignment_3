`timescale 1ns / 1ns


module HLSM36 (Clk, Rst, Start, Done, a, b, c, d, e, f, g, h, i, j, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, aa, bb, cc, dd, ee, ff, gg, hh, ii, final);

	input Clk, Rst, Start;
	output reg Done;
	reg [5:0] State;

	input [31:0] a;
	input [31:0] b;
	input [31:0] c;
	input [31:0] d;
	input [31:0] e;
	input [31:0] f;
	input [31:0] g;
	input [31:0] h;
	input [31:0] i;
	input [31:0] j;
	input [31:0] l;
	input [31:0] m;
	input [31:0] n;
	input [31:0] o;
	input [31:0] p;
	input [31:0] q;
	input [31:0] r;
	input [31:0] s;
	input [31:0] t;
	input [31:0] u;
	input [31:0] v;
	input [31:0] w;
	input [31:0] x;
	input [31:0] y;
	input [31:0] z;
	input [31:0] aa;
	input [31:0] bb;
	input [31:0] cc;
	input [31:0] dd;
	input [31:0] ee;
	input [31:0] ff;
	input [31:0] gg;
	input [31:0] hh;
	input [31:0] ii;

	output reg [31:0] final;

	reg [31:0] t1;
	reg [31:0] t2;
	reg [31:0] t3;
	reg [31:0] t4;
	reg [31:0] t5;
	reg [31:0] t6;
	reg [31:0] t7;
	reg [31:0] t8;
	reg [31:0] t9;
	reg [31:0] t10;
	reg [31:0] t11;
	reg [31:0] t12;
	reg [31:0] t13;
	reg [31:0] t14;
	reg [31:0] t15;
	reg [31:0] t16;
	reg [31:0] t17;
	reg [31:0] t18;
	reg [31:0] t19;
	reg [31:0] t20;
	reg [31:0] t21;
	reg [31:0] t22;
	reg [31:0] t23;
	reg [31:0] t24;
	reg [31:0] t25;
	reg [31:0] t26;
	reg [31:0] t27;
	reg [31:0] t28;
	reg [31:0] t29;
	reg [31:0] t30;
	reg [31:0] t31;
	reg [31:0] t32;
	reg [31:0] t33;



	always @(posedge Clk) begin
		if (Rst) begin
			final <= 0; t1 <= 0; t2 <= 0; t3 <= 0; t4 <= 0; t5 <= 0; t6 <= 0; t7 <= 0; t8 <= 0; t9 <= 0; t10 <= 0; t11 <= 0; t12 <= 0; t13 <= 0; t14 <= 0; t15 <= 0; t16 <= 0; t17 <= 0; t18 <= 0; t19 <= 0; t20 <= 0; t21 <= 0; t22 <= 0; t23 <= 0; t24 <= 0; t25 <= 0; t26 <= 0; t27 <= 0; t28 <= 0; t29 <= 0; t30 <= 0; t31 <= 0; t32 <= 0; t33 <= 0; 
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
					t8 <= t7 + i;
					State <= State + 1;
				end
				10 : begin
					t9 <= t8 + j;
					State <= State + 1;
				end
				11 : begin
					t10 <= t9 + l;
					State <= State + 1;
				end
				12 : begin
					t11 <= t10 + m;
					State <= State + 1;
				end
				13 : begin
					t12 <= t11 + n;
					State <= State + 1;
				end
				14 : begin
					t13 <= t12 + o;
					State <= State + 1;
				end
				15 : begin
					t14 <= t13 + p;
					State <= State + 1;
				end
				16 : begin
					t15 <= t14 + q;
					State <= State + 1;
				end
				17 : begin
					t16 <= t15 + r;
					State <= State + 1;
				end
				18 : begin
					t17 <= t16 + s;
					State <= State + 1;
				end
				19 : begin
					t18 <= t17 + t;
					State <= State + 1;
				end
				20 : begin
					t19 <= t18 + u;
					State <= State + 1;
				end
				21 : begin
					t20 <= t19 + v;
					State <= State + 1;
				end
				22 : begin
					t21 <= t20 + w;
					State <= State + 1;
				end
				23 : begin
					t22 <= t21 + x;
					State <= State + 1;
				end
				24 : begin
					t23 <= t22 + y;
					State <= State + 1;
				end
				25 : begin
					t24 <= t23 + z;
					State <= State + 1;
				end
				26 : begin
					t25 <= t24 + aa;
					State <= State + 1;
				end
				27 : begin
					t26 <= t25 + bb;
					State <= State + 1;
				end
				28 : begin
					t27 <= t26 + cc;
					State <= State + 1;
				end
				29 : begin
					t28 <= t27 + dd;
					State <= State + 1;
				end
				30 : begin
					t29 <= t28 + ee;
					State <= State + 1;
				end
				31 : begin
					t30 <= t29 + ff;
					State <= State + 1;
				end
				32 : begin
					t31 <= t30 + gg;
					State <= State + 1;
				end
				33 : begin
					t32 <= t31 + hh;
					State <= State + 1;
				end
				34 : begin
					t33 <= t32 + ii;
					State <= State + 1;
				end
				35 : begin
					final <= t33 + t1;
					State <= 1;
				end
			endcase
		end
	end
endmodule