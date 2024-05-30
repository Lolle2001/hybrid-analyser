#ifdef __CLING__
#pragma cling optimize(0)
#endif
void c1()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu May 30 14:52:47 2024) by ROOT version 6.30/02
   TCanvas *c1 = new TCanvas("c1", "c1",1920,37,1920,987);
   c1->SetHighLightColor(2);
   c1->Range(-1.18464,-3.125,0.6617614,8.125);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogx();
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[1] = { 0 };
   Double_t Graph0_fy1[1] = { 0 };
   TGraph *graph = new TGraph(1,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","Graph",100,0.1,3);
   Graph_Graph01->SetMinimum(0.01);
   Graph_Graph01->SetMaximum(1e+07);
   Graph_Graph01->SetDirectory(nullptr);
   Graph_Graph01->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01->SetLineColor(ci);
   Graph_Graph01->GetXaxis()->SetLabelFont(42);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01->GetXaxis()->SetTitleFont(42);
   Graph_Graph01->GetYaxis()->SetLabelFont(42);
   Graph_Graph01->GetYaxis()->SetTitleFont(42);
   Graph_Graph01->GetZaxis()->SetLabelFont(42);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("ap");
   
   TF1 *1 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   1->SetRange(0.1,3);
   1->SetName("");
   1->SetTitle("");
   1->SetSavedPoint(0,3899825);
   1->SetSavedPoint(1,3702771);
   1->SetSavedPoint(2,3470670);
   1->SetSavedPoint(3,3217884);
   1->SetSavedPoint(4,2957350);
   1->SetSavedPoint(5,2699138);
   1->SetSavedPoint(6,2450304);
   1->SetSavedPoint(7,2215328);
   1->SetSavedPoint(8,1996712);
   1->SetSavedPoint(9,1795535);
   1->SetSavedPoint(10,1611909);
   1->SetSavedPoint(11,1445324);
   1->SetSavedPoint(12,1294886);
   1->SetSavedPoint(13,1159496);
   1->SetSavedPoint(14,1037959);
   1->SetSavedPoint(15,929065.7);
   1->SetSavedPoint(16,831634.4);
   1->SetSavedPoint(17,744544.5);
   1->SetSavedPoint(18,666750.2);
   1->SetSavedPoint(19,597288.6);
   1->SetSavedPoint(20,535280.7);
   1->SetSavedPoint(21,479930);
   1->SetSavedPoint(22,430518.2);
   1->SetSavedPoint(23,386400.5);
   1->SetSavedPoint(24,346999.2);
   1->SetSavedPoint(25,311798.4);
   1->SetSavedPoint(26,280338);
   1->SetSavedPoint(27,252208.1);
   1->SetSavedPoint(28,227044);
   1->SetSavedPoint(29,204521.4);
   1->SetSavedPoint(30,184352);
   1->SetSavedPoint(31,166279.9);
   1->SetSavedPoint(32,150077.3);
   1->SetSavedPoint(33,135542.3);
   1->SetSavedPoint(34,122495);
   1->SetSavedPoint(35,110776.1);
   1->SetSavedPoint(36,100243.6);
   1->SetSavedPoint(37,90771.26);
   1->SetSavedPoint(38,82247.03);
   1->SetSavedPoint(39,74571.02);
   1->SetSavedPoint(40,67654.39);
   1->SetSavedPoint(41,61417.97);
   1->SetSavedPoint(42,55791.25);
   1->SetSavedPoint(43,50711.36);
   1->SetSavedPoint(44,46122.21);
   1->SetSavedPoint(45,41973.75);
   1->SetSavedPoint(46,38221.29);
   1->SetSavedPoint(47,34824.89);
   1->SetSavedPoint(48,31748.84);
   1->SetSavedPoint(49,28961.2);
   1->SetSavedPoint(50,26433.38);
   1->SetSavedPoint(51,24139.76);
   1->SetSavedPoint(52,22057.39);
   1->SetSavedPoint(53,20165.7);
   1->SetSavedPoint(54,18446.19);
   1->SetSavedPoint(55,16882.3);
   1->SetSavedPoint(56,15459.11);
   1->SetSavedPoint(57,14163.23);
   1->SetSavedPoint(58,12982.61);
   1->SetSavedPoint(59,11906.39);
   1->SetSavedPoint(60,10924.81);
   1->SetSavedPoint(61,10029.06);
   1->SetSavedPoint(62,9211.197);
   1->SetSavedPoint(63,8464.051);
   1->SetSavedPoint(64,7781.154);
   1->SetSavedPoint(65,7156.66);
   1->SetSavedPoint(66,6585.284);
   1->SetSavedPoint(67,6062.247);
   1->SetSavedPoint(68,5583.222);
   1->SetSavedPoint(69,5144.293);
   1->SetSavedPoint(70,4741.91);
   1->SetSavedPoint(71,4372.855);
   1->SetSavedPoint(72,4034.209);
   1->SetSavedPoint(73,3723.325);
   1->SetSavedPoint(74,3437.795);
   1->SetSavedPoint(75,3175.435);
   1->SetSavedPoint(76,2934.258);
   1->SetSavedPoint(77,2712.457);
   1->SetSavedPoint(78,2508.387);
   1->SetSavedPoint(79,2320.551);
   1->SetSavedPoint(80,2147.585);
   1->SetSavedPoint(81,1988.247);
   1->SetSavedPoint(82,1841.402);
   1->SetSavedPoint(83,1706.017);
   1->SetSavedPoint(84,1581.148);
   1->SetSavedPoint(85,1465.933);
   1->SetSavedPoint(86,1359.584);
   1->SetSavedPoint(87,1261.382);
   1->SetSavedPoint(88,1170.668);
   1->SetSavedPoint(89,1086.841);
   1->SetSavedPoint(90,1009.348);
   1->SetSavedPoint(91,937.686);
   1->SetSavedPoint(92,871.3919);
   1->SetSavedPoint(93,810.042);
   1->SetSavedPoint(94,753.2478);
   1->SetSavedPoint(95,700.6529);
   1->SetSavedPoint(96,651.9302);
   1->SetSavedPoint(97,606.7794);
   1->SetSavedPoint(98,564.9248);
   1->SetSavedPoint(99,526.113);
   1->SetSavedPoint(100,490.1111);
   1->SetSavedPoint(101,0.1);
   1->SetSavedPoint(102,3);
   1->SetFillColor(19);
   1->SetFillStyle(0);
   1->SetLineWidth(2);
   1->GetXaxis()->SetLabelFont(42);
   1->GetXaxis()->SetTitleOffset(1);
   1->GetXaxis()->SetTitleFont(42);
   1->GetYaxis()->SetLabelFont(42);
   1->GetYaxis()->SetTitleFont(42);
   1->Draw("L SAME");
   
   Double_t Graph1_fx1001[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph1_fy1001[58] = { 6073917, 5484223, 4979636, 4520342, 4091007, 3414355, 2667569, 2312736, 1852609, 1485715, 1199837, 966486.3, 783865.6, 640060.2, 530645.5, 445566, 374551.5,
   315451.8, 267330.6, 227808.6, 193784.4, 151675.1, 106727.1, 81815.89, 60271.65, 44762.96, 33543.34, 25054.64, 19009.36, 14266.01, 10896.4, 7098.866, 4209.99,
   2539.406, 1560.573, 977.5557, 620.2921, 399.8608, 261.104, 175.3167, 119.615, 65.479, 29.76638, 15.15261, 8.361309, 5.08773, 3.24631, 1.809106, 0.9102422,
   0.5000063, 0.2922927, 0.1802613, 0.1142883, 0.07790189, 0.05261496, 0.03639277, 0.02210895, 0.01206699 };
   Double_t Graph1_fex1001[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph1_fey1001[58] = { 465183, 306161.7, 266341.9, 233995.2, 210292.2, 175309.5, 140146.1, 58263.19, 43768.91, 36039.79, 29850.23, 20983.13, 18456.5, 17847.94, 15929.12, 15686.88, 13733.02,
   11456.87, 9628.383, 8271.794, 6928.616, 5316.923, 3841.871, 3612.118, 2386.101, 1757.775, 1314.074, 1234.605, 928.8345, 701.4306, 566.535, 291.7411, 155.0816,
   81.34691, 47.11923, 30.09962, 19.09621, 11.83147, 7.556716, 5.089302, 3.38246, 1.881863, 0.8209737, 0.4199096, 0.240435, 0.1459471, 0.09694602, 0.06003813, 0.02807766,
   0.01613209, 0.009671258, 0.006294733, 0.00422373, 0.003081356, 0.002195954, 0.001605984, 0.0009507558, 0.0005798295 };
   TGraphErrors *gre = new TGraphErrors(58,Graph1_fx1001,Graph1_fy1001,Graph1_fex1001,Graph1_fey1001);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(206);
   gre->SetMarkerColor(206);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph11001 = new TH1F("Graph_Graph11001","Graph",100,0.09,21.99);
   Graph_Graph11001->SetMinimum(0.01033844);
   Graph_Graph11001->SetMaximum(7193011);
   Graph_Graph11001->SetDirectory(nullptr);
   Graph_Graph11001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11001->SetLineColor(ci);
   Graph_Graph11001->GetXaxis()->SetLabelFont(42);
   Graph_Graph11001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11001->GetXaxis()->SetTitleFont(42);
   Graph_Graph11001->GetYaxis()->SetLabelFont(42);
   Graph_Graph11001->GetYaxis()->SetTitleFont(42);
   Graph_Graph11001->GetZaxis()->SetLabelFont(42);
   Graph_Graph11001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11001);
   
   gre->Draw("p ");
   
   TF1 *2 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   2->SetRange(0.1,3);
   2->SetName("");
   2->SetTitle("");
   2->SetSavedPoint(0,1558191);
   2->SetSavedPoint(1,1480973);
   2->SetSavedPoint(2,1389722);
   2->SetSavedPoint(3,1290048);
   2->SetSavedPoint(4,1187045);
   2->SetSavedPoint(5,1084708);
   2->SetSavedPoint(6,985862.5);
   2->SetSavedPoint(7,892322.8);
   2->SetSavedPoint(8,805122.1);
   2->SetSavedPoint(9,724728.5);
   2->SetSavedPoint(10,651221.8);
   2->SetSavedPoint(11,584428.2);
   2->SetSavedPoint(12,524017.8);
   2->SetSavedPoint(13,469573);
   2->SetSavedPoint(14,420634.4);
   2->SetSavedPoint(15,376732.4);
   2->SetSavedPoint(16,337406.2);
   2->SetSavedPoint(17,302216.2);
   2->SetSavedPoint(18,270750.8);
   2->SetSavedPoint(19,242629.7);
   2->SetSavedPoint(20,217504.6);
   2->SetSavedPoint(21,195059.3);
   2->SetSavedPoint(22,175007.9);
   2->SetSavedPoint(23,157093.1);
   2->SetSavedPoint(24,141084.1);
   2->SetSavedPoint(25,126774.2);
   2->SetSavedPoint(26,113978.9);
   2->SetSavedPoint(27,102533.4);
   2->SetSavedPoint(28,92291.16);
   2->SetSavedPoint(29,83121.35);
   2->SetSavedPoint(30,74907.69);
   2->SetSavedPoint(31,67546.71);
   2->SetSavedPoint(32,60946.36);
   2->SetSavedPoint(33,55024.79);
   2->SetSavedPoint(34,49709.19);
   2->SetSavedPoint(35,44934.79);
   2->SetSavedPoint(36,40643.97);
   2->SetSavedPoint(37,36785.47);
   2->SetSavedPoint(38,33313.65);
   2->SetSavedPoint(39,30187.86);
   2->SetSavedPoint(40,27371.92);
   2->SetSavedPoint(41,24833.56);
   2->SetSavedPoint(42,22544.03);
   2->SetSavedPoint(43,20477.69);
   2->SetSavedPoint(44,18611.63);
   2->SetSavedPoint(45,16925.43);
   2->SetSavedPoint(46,15400.83);
   2->SetSavedPoint(47,14021.52);
   2->SetSavedPoint(48,12772.91);
   2->SetSavedPoint(49,11641.94);
   2->SetSavedPoint(50,10616.93);
   2->SetSavedPoint(51,9687.401);
   2->SetSavedPoint(52,8843.983);
   2->SetSavedPoint(53,8078.255);
   2->SetSavedPoint(54,7382.669);
   2->SetSavedPoint(55,6750.443);
   2->SetSavedPoint(56,6175.488);
   2->SetSavedPoint(57,5652.328);
   2->SetSavedPoint(58,5176.039);
   2->SetSavedPoint(59,4742.19);
   2->SetSavedPoint(60,4346.789);
   2->SetSavedPoint(61,3986.24);
   2->SetSavedPoint(62,3657.301);
   2->SetSavedPoint(63,3357.048);
   2->SetSavedPoint(64,3082.842);
   2->SetSavedPoint(65,2832.297);
   2->SetSavedPoint(66,2603.26);
   2->SetSavedPoint(67,2393.783);
   2->SetSavedPoint(68,2202.104);
   2->SetSavedPoint(69,2026.628);
   2->SetSavedPoint(70,1865.911);
   2->SetSavedPoint(71,1718.644);
   2->SetSavedPoint(72,1583.64);
   2->SetSavedPoint(73,1459.823);
   2->SetSavedPoint(74,1346.216);
   2->SetSavedPoint(75,1241.931);
   2->SetSavedPoint(76,1146.163);
   2->SetSavedPoint(77,1058.179);
   2->SetSavedPoint(78,977.3117);
   2->SetSavedPoint(79,902.9561);
   2->SetSavedPoint(80,834.5596);
   2->SetSavedPoint(81,771.6196);
   2->SetSavedPoint(82,713.6778);
   2->SetSavedPoint(83,660.3166);
   2->SetSavedPoint(84,611.1549);
   2->SetSavedPoint(85,565.845);
   2->SetSavedPoint(86,524.0696);
   2->SetSavedPoint(87,485.5387);
   2->SetSavedPoint(88,449.9874);
   2->SetSavedPoint(89,417.1735);
   2->SetSavedPoint(90,386.8754);
   2->SetSavedPoint(91,358.8905);
   2->SetSavedPoint(92,333.0331);
   2->SetSavedPoint(93,309.1335);
   2->SetSavedPoint(94,287.0358);
   2->SetSavedPoint(95,266.5976);
   2->SetSavedPoint(96,247.6878);
   2->SetSavedPoint(97,230.1865);
   2->SetSavedPoint(98,213.9837);
   2->SetSavedPoint(99,198.9782);
   2->SetSavedPoint(100,185.0772);
   2->SetSavedPoint(101,0.1);
   2->SetSavedPoint(102,3);
   2->SetFillColor(19);
   2->SetFillStyle(0);
   2->SetLineWidth(2);
   2->GetXaxis()->SetLabelFont(42);
   2->GetXaxis()->SetTitleOffset(1);
   2->GetXaxis()->SetTitleFont(42);
   2->GetYaxis()->SetLabelFont(42);
   2->GetYaxis()->SetTitleFont(42);
   2->Draw("L SAME");
   
   Double_t Graph2_fx1002[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph2_fy1002[58] = { 2340316, 2161169, 1984705, 1810265, 1647073, 1376955, 1082330, 941692.7, 754203.3, 604693.5, 488786.7, 392939.7, 322264.7, 260091.9, 214701.6, 180591.7, 151406.6,
   127685.2, 108170.5, 92206.66, 78085.76, 61441.45, 43298.82, 33360.26, 24615.21, 18317.23, 13678.31, 10244.69, 7707.77, 5902.149, 4476.705, 2921.748, 1736.318,
   1057.64, 657.2104, 414.4839, 266.064, 171.7704, 113.6958, 77.32047, 53.12138, 29.41098, 13.58694, 6.966313, 3.883048, 2.346131, 1.491303, 0.8295845, 0.417196,
   0.225454, 0.1323168, 0.07968469, 0.05146088, 0.03422589, 0.02315364, 0.01611557, 0.009909818, 0.005295304 };
   Double_t Graph2_fex1002[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph2_fey1002[58] = { 185629.6, 127111.3, 112023.6, 99095.02, 89506.46, 74148.04, 59511, 22785.91, 16417.94, 12927.99, 10677.65, 7789.444, 6455.299, 7011.04, 6506.407, 6381.121, 5612.595,
   4663.782, 3910.107, 3381.715, 2816.954, 2165.011, 1567.519, 1494.517, 983.866, 727.4099, 538.9183, 511.2071, 381.6401, 292.8293, 236.3977, 125.8791, 65.19759,
   34.80415, 20.50227, 12.96587, 8.287682, 4.775256, 3.176283, 2.289354, 1.54192, 0.8382496, 0.3638487, 0.2056119, 0.1125829, 0.06733644, 0.04550132, 0.02443555, 0.01269208,
   0.007180835, 0.004440315, 0.002830544, 0.001932697, 0.001369398, 0.0009790956, 0.0007217675, 0.0004309817, 0.00025949 };
   gre = new TGraphErrors(58,Graph2_fx1002,Graph2_fy1002,Graph2_fex1002,Graph2_fey1002);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(94);
   gre->SetMarkerColor(94);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph21002 = new TH1F("Graph_Graph21002","Graph",100,0.09,21.99);
   Graph_Graph21002->SetMinimum(0.004532233);
   Graph_Graph21002->SetMaximum(2778540);
   Graph_Graph21002->SetDirectory(nullptr);
   Graph_Graph21002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21002->SetLineColor(ci);
   Graph_Graph21002->GetXaxis()->SetLabelFont(42);
   Graph_Graph21002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21002->GetXaxis()->SetTitleFont(42);
   Graph_Graph21002->GetYaxis()->SetLabelFont(42);
   Graph_Graph21002->GetYaxis()->SetTitleFont(42);
   Graph_Graph21002->GetZaxis()->SetLabelFont(42);
   Graph_Graph21002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21002);
   
   gre->Draw("p ");
   
   TF1 *3 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   3->SetRange(0.1,3);
   3->SetName("");
   3->SetTitle("");
   3->SetSavedPoint(0,577773.5);
   3->SetSavedPoint(1,549368.8);
   3->SetSavedPoint(2,515783.7);
   3->SetSavedPoint(3,479071.5);
   3->SetSavedPoint(4,441099.7);
   3->SetSavedPoint(5,403336.9);
   3->SetSavedPoint(6,366825.1);
   3->SetSavedPoint(7,332237.1);
   3->SetSavedPoint(8,299959.8);
   3->SetSavedPoint(9,270171.9);
   3->SetSavedPoint(10,242909.1);
   3->SetSavedPoint(11,218112.8);
   3->SetSavedPoint(12,195665.9);
   3->SetSavedPoint(13,175418.2);
   3->SetSavedPoint(14,157203.3);
   3->SetSavedPoint(15,140850.1);
   3->SetSavedPoint(16,126190.5);
   3->SetSavedPoint(17,113063.4);
   3->SetSavedPoint(18,101317.9);
   3->SetSavedPoint(19,90814.16);
   3->SetSavedPoint(20,81423.94);
   3->SetSavedPoint(21,73030.62);
   3->SetSavedPoint(22,65528.66);
   3->SetSavedPoint(23,58822.93);
   3->SetSavedPoint(24,52827.99);
   3->SetSavedPoint(25,47467.27);
   3->SetSavedPoint(26,42672.29);
   3->SetSavedPoint(27,38381.9);
   3->SetSavedPoint(28,34541.55);
   3->SetSavedPoint(29,31102.6);
   3->SetSavedPoint(30,28021.73);
   3->SetSavedPoint(31,25260.35);
   3->SetSavedPoint(32,22784.13);
   3->SetSavedPoint(33,20562.49);
   3->SetSavedPoint(34,18568.21);
   3->SetSavedPoint(35,16777.08);
   3->SetSavedPoint(36,15167.51);
   3->SetSavedPoint(37,13720.32);
   3->SetSavedPoint(38,12418.38);
   3->SetSavedPoint(39,11246.46);
   3->SetSavedPoint(40,10190.97);
   3->SetSavedPoint(41,9239.814);
   3->SetSavedPoint(42,8382.176);
   3->SetSavedPoint(43,7608.421);
   3->SetSavedPoint(44,6909.946);
   3->SetSavedPoint(45,6279.064);
   3->SetSavedPoint(46,5708.91);
   3->SetSavedPoint(47,5193.346);
   3->SetSavedPoint(48,4726.88);
   3->SetSavedPoint(49,4304.6);
   3->SetSavedPoint(50,3922.105);
   3->SetSavedPoint(51,3575.456);
   3->SetSavedPoint(52,3261.119);
   3->SetSavedPoint(53,2975.927);
   3->SetSavedPoint(54,2717.038);
   3->SetSavedPoint(55,2481.898);
   3->SetSavedPoint(56,2268.217);
   3->SetSavedPoint(57,2073.932);
   3->SetSavedPoint(58,1897.193);
   3->SetSavedPoint(59,1736.33);
   3->SetSavedPoint(60,1589.844);
   3->SetSavedPoint(61,1456.383);
   3->SetSavedPoint(62,1334.727);
   3->SetSavedPoint(63,1223.777);
   3->SetSavedPoint(64,1122.543);
   3->SetSavedPoint(65,1030.13);
   3->SetSavedPoint(66,945.7276);
   3->SetSavedPoint(67,868.6066);
   3->SetSavedPoint(68,798.106);
   3->SetSavedPoint(69,733.628);
   3->SetSavedPoint(70,674.6315);
   3->SetSavedPoint(71,620.6266);
   3->SetSavedPoint(72,571.1692);
   3->SetSavedPoint(73,525.8568);
   3->SetSavedPoint(74,484.3242);
   3->SetSavedPoint(75,446.2401);
   3->SetSavedPoint(76,411.3037);
   3->SetSavedPoint(77,379.2415);
   3->SetSavedPoint(78,349.8053);
   3->SetSavedPoint(79,322.7691);
   3->SetSavedPoint(80,297.9275);
   3->SetSavedPoint(81,275.0934);
   3->SetSavedPoint(82,254.0966);
   3->SetSavedPoint(83,234.7819);
   3->SetSavedPoint(84,217.0079);
   3->SetSavedPoint(85,200.6456);
   3->SetSavedPoint(86,185.5775);
   3->SetSavedPoint(87,171.6962);
   3->SetSavedPoint(88,158.9037);
   3->SetSavedPoint(89,147.1104);
   3->SetSavedPoint(90,136.2346);
   3->SetSavedPoint(91,126.2014);
   3->SetSavedPoint(92,116.9425);
   3->SetSavedPoint(93,108.3952);
   3->SetSavedPoint(94,100.5023);
   3->SetSavedPoint(95,93.21128);
   3->SetSavedPoint(96,86.4741);
   3->SetSavedPoint(97,80.24671);
   3->SetSavedPoint(98,74.48874);
   3->SetSavedPoint(99,69.16316);
   3->SetSavedPoint(100,64.236);
   3->SetSavedPoint(101,0.1);
   3->SetSavedPoint(102,3);
   3->SetFillColor(19);
   3->SetFillStyle(0);
   3->SetLineWidth(2);
   3->GetXaxis()->SetLabelFont(42);
   3->GetXaxis()->SetTitleOffset(1);
   3->GetXaxis()->SetTitleFont(42);
   3->GetYaxis()->SetLabelFont(42);
   3->GetYaxis()->SetTitleFont(42);
   3->Draw("L SAME");
   
   Double_t Graph3_fx1003[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph3_fy1003[58] = { 915102.7, 835621.2, 764133.9, 697243.9, 628052.9, 526154.6, 411111, 352225.9, 281685.4, 225672, 181845.4, 146731.5, 120166.2, 97293.27, 80523.97, 67586.15, 56849.77,
   47884.92, 40582.55, 34574.41, 29333.77, 23031.42, 16199.68, 12522.97, 9232.213, 6882.027, 5149.474, 3904.774, 2938.713, 2248.257, 1712.32, 1112.651, 665.9995,
   408.3493, 254.0896, 161.5697, 104.3984, 68.6148, 46.06828, 31.01144, 21.83234, 12.18149, 5.716636, 2.945185, 1.654972, 1.003481, 0.6402128, 0.3556107, 0.1768179,
   0.09594919, 0.0553881, 0.03347783, 0.02137445, 0.01425183, 0.009690249, 0.006611514, 0.003945569, 0.002135654 };
   Double_t Graph3_fex1003[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph3_fey1003[58] = { 68728.79, 45002.38, 39291.51, 34612.41, 30935.34, 25791.83, 20663.29, 8364.035, 5987.211, 4729.352, 3861.625, 2882.28, 2384.393, 2551.492, 2411.763, 2360.061, 2235.287,
   1727.671, 1444.714, 1242.446, 1036.529, 798.0698, 574.317, 472.2165, 360.0291, 269.5899, 199.2428, 189.6576, 142.4338, 109.3727, 87.95283, 46.79115, 24.08911,
   12.79713, 7.484279, 4.670404, 3.109215, 1.947646, 1.233995, 0.8497279, 0.605781, 0.3093892, 0.1461008, 0.07363195, 0.0437064, 0.02821365, 0.01852503, 0.01057304, 0.005205468,
   0.002926304, 0.001767049, 0.001117624, 0.0007473822, 0.0005373395, 0.000382288, 0.0002738921, 0.0001597967, 9.549629e-05 };
   gre = new TGraphErrors(58,Graph3_fx1003,Graph3_fy1003,Graph3_fex1003,Graph3_fey1003);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ffcc66");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ffcc66");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph31003 = new TH1F("Graph_Graph31003","Graph",100,0.09,21.99);
   Graph_Graph31003->SetMinimum(0.001836142);
   Graph_Graph31003->SetMaximum(1082215);
   Graph_Graph31003->SetDirectory(nullptr);
   Graph_Graph31003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31003->SetLineColor(ci);
   Graph_Graph31003->GetXaxis()->SetLabelFont(42);
   Graph_Graph31003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31003->GetXaxis()->SetTitleFont(42);
   Graph_Graph31003->GetYaxis()->SetLabelFont(42);
   Graph_Graph31003->GetYaxis()->SetTitleFont(42);
   Graph_Graph31003->GetZaxis()->SetLabelFont(42);
   Graph_Graph31003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31003);
   
   gre->Draw("p ");
   
   TF1 *4 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   4->SetRange(0.1,3);
   4->SetName("");
   4->SetTitle("");
   4->SetSavedPoint(0,198296.5);
   4->SetSavedPoint(1,188251);
   4->SetSavedPoint(2,176449.4);
   4->SetSavedPoint(3,163617.1);
   4->SetSavedPoint(4,150403.3);
   4->SetSavedPoint(5,137311.9);
   4->SetSavedPoint(6,124695.6);
   4->SetSavedPoint(7,112778.5);
   4->SetSavedPoint(8,101685.9);
   4->SetSavedPoint(9,91472.37);
   4->SetSavedPoint(10,82143.93);
   4->SetSavedPoint(11,73675.34);
   4->SetSavedPoint(12,66022.26);
   4->SetSavedPoint(13,59129.73);
   4->SetSavedPoint(14,52938.06);
   4->SetSavedPoint(15,47386.57);
   4->SetSavedPoint(16,42416.02);
   4->SetSavedPoint(17,37970.1);
   4->SetSavedPoint(18,33996.24);
   4->SetSavedPoint(19,30445.94);
   4->SetSavedPoint(20,27274.91);
   4->SetSavedPoint(21,24442.96);
   4->SetSavedPoint(22,21913.83);
   4->SetSavedPoint(23,19654.9);
   4->SetSavedPoint(24,17636.92);
   4->SetSavedPoint(25,15833.76);
   4->SetSavedPoint(26,14222.04);
   4->SetSavedPoint(27,12780.94);
   4->SetSavedPoint(28,11491.91);
   4->SetSavedPoint(29,10338.42);
   4->SetSavedPoint(30,9305.753);
   4->SetSavedPoint(31,8380.833);
   4->SetSavedPoint(32,7552.018);
   4->SetSavedPoint(33,6808.952);
   4->SetSavedPoint(34,6142.425);
   4->SetSavedPoint(35,5544.242);
   4->SetSavedPoint(36,5007.113);
   4->SetSavedPoint(37,4524.547);
   4->SetSavedPoint(38,4090.768);
   4->SetSavedPoint(39,3700.63);
   4->SetSavedPoint(40,3349.552);
   4->SetSavedPoint(41,3033.447);
   4->SetSavedPoint(42,2748.677);
   4->SetSavedPoint(43,2491.991);
   4->SetSavedPoint(44,2260.494);
   4->SetSavedPoint(45,2051.598);
   4->SetSavedPoint(46,1862.993);
   4->SetSavedPoint(47,1692.615);
   4->SetSavedPoint(48,1538.618);
   4->SetSavedPoint(49,1399.351);
   4->SetSavedPoint(50,1273.339);
   4->SetSavedPoint(51,1159.257);
   4->SetSavedPoint(52,1055.921);
   4->SetSavedPoint(53,962.2708);
   4->SetSavedPoint(54,877.3526);
   4->SetSavedPoint(55,800.3126);
   4->SetSavedPoint(56,730.384);
   4->SetSavedPoint(57,666.8778);
   4->SetSavedPoint(58,609.1753);
   4->SetSavedPoint(59,556.7197);
   4->SetSavedPoint(60,509.0104);
   4->SetSavedPoint(61,465.5966);
   4->SetSavedPoint(62,426.0727);
   4->SetSavedPoint(63,390.0727);
   4->SetSavedPoint(64,357.2671);
   4->SetSavedPoint(65,327.3584);
   4->SetSavedPoint(66,300.0783);
   4->SetSavedPoint(67,275.1844);
   4->SetSavedPoint(68,252.4577);
   4->SetSavedPoint(69,231.7003);
   4->SetSavedPoint(70,212.7334);
   4->SetSavedPoint(71,195.3949);
   4->SetSavedPoint(72,179.5382);
   4->SetSavedPoint(73,165.0307);
   4->SetSavedPoint(74,151.752);
   4->SetSavedPoint(75,139.5929);
   4->SetSavedPoint(76,128.4547);
   4->SetSavedPoint(77,118.2474);
   4->SetSavedPoint(78,108.8897);
   4->SetSavedPoint(79,100.3073);
   4->SetSavedPoint(80,92.43319);
   4->SetSavedPoint(81,85.20601);
   4->SetSavedPoint(82,78.57018);
   4->SetSavedPoint(83,72.47505);
   4->SetSavedPoint(84,66.87453);
   4->SetSavedPoint(85,61.72662);
   4->SetSavedPoint(86,56.99307);
   4->SetSavedPoint(87,52.639);
   4->SetSavedPoint(88,48.6326);
   4->SetSavedPoint(89,44.94485);
   4->SetSavedPoint(90,41.54927);
   4->SetSavedPoint(91,38.42166);
   4->SetSavedPoint(92,35.53993);
   4->SetSavedPoint(93,32.8839);
   4->SetSavedPoint(94,30.43509);
   4->SetSavedPoint(95,28.17663);
   4->SetSavedPoint(96,26.09307);
   4->SetSavedPoint(97,24.17027);
   4->SetSavedPoint(98,22.39529);
   4->SetSavedPoint(99,20.75628);
   4->SetSavedPoint(100,19.24236);
   4->SetSavedPoint(101,0.1);
   4->SetSavedPoint(102,3);
   4->SetFillColor(19);
   4->SetFillStyle(0);
   4->SetLineWidth(2);
   4->GetXaxis()->SetLabelFont(42);
   4->GetXaxis()->SetTitleOffset(1);
   4->GetXaxis()->SetTitleFont(42);
   4->GetYaxis()->SetLabelFont(42);
   4->GetYaxis()->SetTitleFont(42);
   4->Draw("L SAME");
   
   Double_t Graph4_fx1004[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph4_fy1004[58] = { 335298.1, 302198.9, 275182.7, 248704.1, 224133, 185591.9, 144256.3, 120048.4, 95530.31, 76256.8, 61290.48, 49361.14, 40297.26, 32765.08, 26988, 22715.3, 19033.86,
   15982.88, 13486.39, 11474.3, 9708.693, 7629.154, 5370.369, 4132.386, 3066.036, 2291.761, 1700.982, 1293.574, 971.2824, 749.8376, 573.7753, 375.9282, 227.6685,
   140.4597, 87.41931, 56.94138, 37.17005, 24.724, 16.77708, 11.50953, 8.045725, 4.60969, 2.206076, 1.153395, 0.6553849, 0.3846919, 0.2461581, 0.1361327, 0.06700176,
   0.03600325, 0.02073348, 0.0125905, 0.007878521, 0.00515513, 0.003451972, 0.002387894, 0.001438731, 0.0007801983 };
   Double_t Graph4_fex1004[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph4_fey1004[58] = { 25851.08, 17070.09, 14908.11, 13050.75, 11683.03, 9608.787, 7640.83, 3086.076, 2127.754, 1641.64, 1334.756, 1002.381, 823.8851, 857.7383, 822.7685, 803.5584, 702.4576,
   583.0695, 488.138, 418.7387, 347.8368, 266.32, 191.6943, 156.3175, 119.9255, 89.09403, 65.94191, 62.81883, 46.63147, 36.28829, 29.12002, 14.79717, 7.918283,
   4.068614, 2.350019, 1.556492, 1.046889, 0.6685418, 0.4569507, 0.3215853, 0.2156061, 0.1155337, 0.05875065, 0.03039012, 0.01826025, 0.01206547, 0.007557377, 0.004227726, 0.00221056,
   0.001223202, 0.000718012, 0.0004548481, 0.0002985142, 0.0002084265, 0.0001464946, 0.0001065013, 6.269012e-05, 3.763492e-05 };
   gre = new TGraphErrors(58,Graph4_fx1004,Graph4_fy1004,Graph4_fex1004,Graph4_fey1004);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ccff66");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ccff66");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph41004 = new TH1F("Graph_Graph41004","Graph",100,0.09,21.99);
   Graph_Graph41004->SetMinimum(0.000668307);
   Graph_Graph41004->SetMaximum(397264.1);
   Graph_Graph41004->SetDirectory(nullptr);
   Graph_Graph41004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41004->SetLineColor(ci);
   Graph_Graph41004->GetXaxis()->SetLabelFont(42);
   Graph_Graph41004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41004->GetXaxis()->SetTitleFont(42);
   Graph_Graph41004->GetYaxis()->SetLabelFont(42);
   Graph_Graph41004->GetYaxis()->SetTitleFont(42);
   Graph_Graph41004->GetZaxis()->SetLabelFont(42);
   Graph_Graph41004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41004);
   
   gre->Draw("p ");
   
   TF1 *5 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   5->SetRange(0.1,3);
   5->SetName("");
   5->SetTitle("");
   5->SetSavedPoint(0,66639.02);
   5->SetSavedPoint(1,63092.98);
   5->SetSavedPoint(2,58965.28);
   5->SetSavedPoint(3,54512.78);
   5->SetSavedPoint(4,49959.99);
   5->SetSavedPoint(5,45477.56);
   5->SetSavedPoint(6,41182.19);
   5->SetSavedPoint(7,37145.73);
   5->SetSavedPoint(8,33406.27);
   5->SetSavedPoint(9,29978.1);
   5->SetSavedPoint(10,26859.6);
   5->SetSavedPoint(11,24039.09);
   5->SetSavedPoint(12,21498.99);
   5->SetSavedPoint(13,19218.65);
   5->SetSavedPoint(14,17176.28);
   5->SetSavedPoint(15,15350.12);
   5->SetSavedPoint(16,13719.24);
   5->SetSavedPoint(17,12263.94);
   5->SetSavedPoint(18,10966);
   5->SetSavedPoint(19,9808.749);
   5->SetSavedPoint(20,8777.049);
   5->SetSavedPoint(21,7857.257);
   5->SetSavedPoint(22,7037.119);
   5->SetSavedPoint(23,6305.673);
   5->SetSavedPoint(24,5653.135);
   5->SetSavedPoint(25,5070.788);
   5->SetSavedPoint(26,4550.875);
   5->SetSavedPoint(27,4086.502);
   5->SetSavedPoint(28,3671.546);
   5->SetSavedPoint(29,3300.569);
   5->SetSavedPoint(30,2968.744);
   5->SetSavedPoint(31,2671.786);
   5->SetSavedPoint(32,2405.892);
   5->SetSavedPoint(33,2167.685);
   5->SetSavedPoint(34,1954.165);
   5->SetSavedPoint(35,1762.671);
   5->SetSavedPoint(36,1590.835);
   5->SetSavedPoint(37,1436.553);
   5->SetSavedPoint(38,1297.956);
   5->SetSavedPoint(39,1173.379);
   5->SetSavedPoint(40,1061.343);
   5->SetSavedPoint(41,960.5274);
   5->SetSavedPoint(42,869.7595);
   5->SetSavedPoint(43,787.9923);
   5->SetSavedPoint(44,714.2926);
   5->SetSavedPoint(45,647.828);
   5->SetSavedPoint(46,587.8555);
   5->SetSavedPoint(47,533.7115);
   5->SetSavedPoint(48,484.8031);
   5->SetSavedPoint(49,440.6004);
   5->SetSavedPoint(50,400.6292);
   5->SetSavedPoint(51,364.4655);
   5->SetSavedPoint(52,331.7294);
   5->SetSavedPoint(53,302.0805);
   5->SetSavedPoint(54,275.2139);
   5->SetSavedPoint(55,250.856);
   5->SetSavedPoint(56,228.7614);
   5->SetSavedPoint(57,208.7098);
   5->SetSavedPoint(58,190.5031);
   5->SetSavedPoint(59,173.9635);
   5->SetSavedPoint(60,158.9311);
   5->SetSavedPoint(61,145.2618);
   5->SetSavedPoint(62,132.8263);
   5->SetSavedPoint(63,121.5077);
   5->SetSavedPoint(64,111.201);
   5->SetSavedPoint(65,101.8114);
   5->SetSavedPoint(66,93.25334);
   5->SetSavedPoint(67,85.44971);
   5->SetSavedPoint(68,78.33081);
   5->SetSavedPoint(69,71.83371);
   5->SetSavedPoint(70,65.90152);
   5->SetSavedPoint(71,60.4828);
   5->SetSavedPoint(72,55.53099);
   5->SetSavedPoint(73,51.00396);
   5->SetSavedPoint(74,46.86356);
   5->SetSavedPoint(75,43.07523);
   5->SetSavedPoint(76,39.60761);
   5->SetSavedPoint(77,36.43229);
   5->SetSavedPoint(78,33.52349);
   5->SetSavedPoint(79,30.85779);
   5->SetSavedPoint(80,28.41393);
   5->SetSavedPoint(81,26.17261);
   5->SetSavedPoint(82,24.11626);
   5->SetSavedPoint(83,22.22892);
   5->SetSavedPoint(84,20.49606);
   5->SetSavedPoint(85,18.90446);
   5->SetSavedPoint(86,17.44208);
   5->SetSavedPoint(87,16.09796);
   5->SetSavedPoint(88,14.8621);
   5->SetSavedPoint(89,13.7254);
   5->SetSavedPoint(90,12.67953);
   5->SetSavedPoint(91,11.71691);
   5->SetSavedPoint(92,10.83063);
   5->SetSavedPoint(93,10.01437);
   5->SetSavedPoint(94,9.262336);
   5->SetSavedPoint(95,8.569265);
   5->SetSavedPoint(96,7.930329);
   5->SetSavedPoint(97,7.341114);
   5->SetSavedPoint(98,6.797583);
   5->SetSavedPoint(99,6.296041);
   5->SetSavedPoint(100,5.833103);
   5->SetSavedPoint(101,0.1);
   5->SetSavedPoint(102,3);
   5->SetFillColor(19);
   5->SetFillStyle(0);
   5->SetLineWidth(2);
   5->GetXaxis()->SetLabelFont(42);
   5->GetXaxis()->SetTitleOffset(1);
   5->GetXaxis()->SetTitleFont(42);
   5->GetYaxis()->SetLabelFont(42);
   5->GetYaxis()->SetTitleFont(42);
   5->Draw("L SAME");
   
   Double_t Graph5_fx1005[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph5_fy1005[58] = { 115045.3, 103098.7, 93470.04, 84227.94, 75539.83, 62361.35, 48077.53, 39466.82, 31307.43, 24858.43, 19903.5, 16019.63, 13035.14, 10600.2, 8695, 7341.447, 5931.489,
   5130.245, 4338.153, 3652.394, 3110.1, 2426.964, 1688.666, 1315.401, 964.9156, 723.3827, 538.6707, 409.98, 310.6181, 236.6436, 183.2211, 118.7193, 72.26421,
   44.85552, 28.57715, 18.47725, 12.18958, 8.137621, 5.605979, 3.866794, 2.765659, 1.603, 0.7823213, 0.4167107, 0.2347331, 0.1404287, 0.08955156, 0.04928354, 0.02418017,
   0.01296249, 0.007410885, 0.004363115, 0.00273227, 0.001824109, 0.001192188, 0.0008217734, 0.0004869707, 0.0002565457 };
   Double_t Graph5_fex1005[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph5_fey1005[58] = { 8597.636, 5448.619, 4703.068, 4083.174, 3632.501, 2965.614, 2349.65, 991.4056, 676.3568, 523.778, 422.565, 322.6627, 266.719, 268.286, 267.5027, 261.9542, 241.8176,
   188.9667, 158.7364, 134.8527, 112.9034, 85.67675, 61.02409, 50.44261, 38.28139, 28.58562, 21.14991, 19.99502, 14.98773, 11.50767, 9.321273, 4.179165, 2.240007,
   1.25823, 0.7643059, 0.4964616, 0.3255682, 0.2137079, 0.1481056, 0.1041579, 0.07360813, 0.03965845, 0.01985889, 0.01067988, 0.00645741, 0.004376456, 0.002715309, 0.001571836, 0.0007964596,
   0.0004413826, 0.0002581907, 0.0001600004, 0.0001057021, 7.575756e-05, 5.251437e-05, 3.827144e-05, 2.213304e-05, 1.3169e-05 };
   gre = new TGraphErrors(58,Graph5_fx1005,Graph5_fy1005,Graph5_fex1005,Graph5_fey1005);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#99ff99");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#99ff99");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph51005 = new TH1F("Graph_Graph51005","Graph",100,0.09,21.99);
   Graph_Graph51005->SetMinimum(0.000219039);
   Graph_Graph51005->SetMaximum(136007.2);
   Graph_Graph51005->SetDirectory(nullptr);
   Graph_Graph51005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51005->SetLineColor(ci);
   Graph_Graph51005->GetXaxis()->SetLabelFont(42);
   Graph_Graph51005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51005->GetXaxis()->SetTitleFont(42);
   Graph_Graph51005->GetYaxis()->SetLabelFont(42);
   Graph_Graph51005->GetYaxis()->SetTitleFont(42);
   Graph_Graph51005->GetZaxis()->SetLabelFont(42);
   Graph_Graph51005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51005);
   
   gre->Draw("p ");
   
   TF1 *6 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   6->SetRange(0.1,3);
   6->SetName("");
   6->SetTitle("");
   6->SetSavedPoint(0,21414.7);
   6->SetSavedPoint(1,20219.02);
   6->SetSavedPoint(2,18837.62);
   6->SetSavedPoint(3,17357.67);
   6->SetSavedPoint(4,15853.9);
   6->SetSavedPoint(5,14382.06);
   6->SetSavedPoint(6,12979.41);
   6->SetSavedPoint(7,11668.19);
   6->SetSavedPoint(8,10459.49);
   6->SetSavedPoint(9,9356.64);
   6->SetSavedPoint(10,8357.954);
   6->SetSavedPoint(11,7458.61);
   6->SetSavedPoint(12,6652.038);
   6->SetSavedPoint(13,5930.828);
   6->SetSavedPoint(14,5287.337);
   6->SetSavedPoint(15,4714.061);
   6->SetSavedPoint(16,4203.863);
   6->SetSavedPoint(17,3750.1);
   6->SetSavedPoint(18,3346.672);
   6->SetSavedPoint(19,2988.044);
   6->SetSavedPoint(20,2669.224);
   6->SetSavedPoint(21,2385.742);
   6->SetSavedPoint(22,2133.605);
   6->SetSavedPoint(23,1909.262);
   6->SetSavedPoint(24,1709.562);
   6->SetSavedPoint(25,1531.707);
   6->SetSavedPoint(26,1373.225);
   6->SetSavedPoint(27,1231.925);
   6->SetSavedPoint(28,1105.87);
   6->SetSavedPoint(29,993.3476);
   6->SetSavedPoint(30,892.8425);
   6->SetSavedPoint(31,803.0155);
   6->SetSavedPoint(32,722.6815);
   6->SetSavedPoint(33,650.7918);
   6->SetSavedPoint(34,586.418);
   6->SetSavedPoint(35,528.7378);
   6->SetSavedPoint(36,477.0225);
   6->SetSavedPoint(37,430.6261);
   6->SetSavedPoint(38,388.9756);
   6->SetSavedPoint(39,351.5622);
   6->SetSavedPoint(40,317.9341);
   6->SetSavedPoint(41,287.6899);
   6->SetSavedPoint(42,260.4724);
   6->SetSavedPoint(43,235.9642);
   6->SetSavedPoint(44,213.8822);
   6->SetSavedPoint(45,193.9746);
   6->SetSavedPoint(46,176.0167);
   6->SetSavedPoint(47,159.8083);
   6->SetSavedPoint(48,145.1704);
   6->SetSavedPoint(49,131.9435);
   6->SetSavedPoint(50,119.9847);
   6->SetSavedPoint(51,109.1665);
   6->SetSavedPoint(52,99.37469);
   6->SetSavedPoint(53,90.50712);
   6->SetSavedPoint(54,82.47219);
   6->SetSavedPoint(55,75.18785);
   6->SetSavedPoint(56,68.5805);
   6->SetSavedPoint(57,62.5841);
   6->SetSavedPoint(58,57.13935);
   6->SetSavedPoint(59,52.19298);
   6->SetSavedPoint(60,47.69711);
   6->SetSavedPoint(61,43.60866);
   6->SetSavedPoint(62,39.88889);
   6->SetSavedPoint(63,36.50289);
   6->SetSavedPoint(64,33.41924);
   6->SetSavedPoint(65,30.60958);
   6->SetSavedPoint(66,28.04838);
   6->SetSavedPoint(67,25.71256);
   6->SetSavedPoint(68,23.58132);
   6->SetSavedPoint(69,21.63584);
   6->SetSavedPoint(70,19.85914);
   6->SetSavedPoint(71,18.23585);
   6->SetSavedPoint(72,16.75206);
   6->SetSavedPoint(73,15.3952);
   6->SetSavedPoint(74,14.15387);
   6->SetSavedPoint(75,13.01776);
   6->SetSavedPoint(76,11.9775);
   6->SetSavedPoint(77,11.02461);
   6->SetSavedPoint(78,10.15139);
   6->SetSavedPoint(79,9.350849);
   6->SetSavedPoint(80,8.616648);
   6->SetSavedPoint(81,7.943017);
   6->SetSavedPoint(82,7.324715);
   6->SetSavedPoint(83,6.756976);
   6->SetSavedPoint(84,6.235463);
   6->SetSavedPoint(85,5.756228);
   6->SetSavedPoint(86,5.315679);
   6->SetSavedPoint(87,4.910539);
   6->SetSavedPoint(88,4.537826);
   6->SetSavedPoint(89,4.194817);
   6->SetSavedPoint(90,3.879032);
   6->SetSavedPoint(91,3.588205);
   6->SetSavedPoint(92,3.320268);
   6->SetSavedPoint(93,3.073333);
   6->SetSavedPoint(94,2.845674);
   6->SetSavedPoint(95,2.635715);
   6->SetSavedPoint(96,2.442014);
   6->SetSavedPoint(97,2.263251);
   6->SetSavedPoint(98,2.098219);
   6->SetSavedPoint(99,1.945813);
   6->SetSavedPoint(100,1.805022);
   6->SetSavedPoint(101,0.1);
   6->SetSavedPoint(102,3);
   6->SetFillColor(19);
   6->SetFillStyle(0);
   6->SetLineWidth(2);
   6->GetXaxis()->SetLabelFont(42);
   6->GetXaxis()->SetTitleOffset(1);
   6->GetXaxis()->SetTitleFont(42);
   6->GetYaxis()->SetLabelFont(42);
   6->GetYaxis()->SetTitleFont(42);
   6->Draw("L SAME");
   
   Double_t Graph6_fx1006[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph6_fy1006[58] = { 38276.82, 34166.7, 30811.04, 27782.99, 24649.92, 20114.69, 15370.73, 12450.64, 9795.864, 7734.346, 6153.58, 4929.595, 3997.308, 3234.558, 2640.19, 2216.455, 1843.979,
   1543.321, 1301.12, 1100.057, 923.6798, 716.6908, 497.7902, 386.8611, 287.6805, 211.7828, 159.5903, 120.3173, 91.03881, 69.73774, 52.65335, 35.34367, 21.78945,
   13.60594, 8.745175, 5.766985, 3.815119, 2.616824, 1.797756, 1.276873, 0.9109866, 0.5400693, 0.2639975, 0.144966, 0.0829789, 0.04870172, 0.03131226, 0.01730519, 0.008439571,
   0.004513004, 0.002552106, 0.001521422, 0.0009177918, 0.0006027346, 0.0003973772, 0.0002706234, 0.0001672827, 8.757744e-05 };
   Double_t Graph6_fex1006[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph6_fey1006[58] = { 2859.131, 1786.343, 1530.814, 1326.967, 1168.116, 937.3216, 737.4122, 336.7245, 229.631, 176.7796, 142.3764, 110.8243, 89.84474, 84.86857, 84.82228, 83.18592, 72.01758,
   59.81022, 50.65485, 42.93204, 35.63629, 26.66547, 19.10754, 15.67906, 12.06043, 8.834842, 6.594297, 5.950094, 4.510463, 3.449706, 2.733419, 1.42774, 0.7315481,
   0.3976093, 0.2497474, 0.1657038, 0.1068023, 0.07647061, 0.05094733, 0.03742856, 0.02803922, 0.01441127, 0.006886323, 0.004047456, 0.002555035, 0.001595848, 0.001002083, 0.0005612712, 0.0002845993,
   0.0001580372, 9.562247e-05, 6.022357e-05, 3.880101e-05, 2.703191e-05, 1.899428e-05, 1.386073e-05, 8.283067e-06, 4.974962e-06 };
   gre = new TGraphErrors(58,Graph6_fx1006,Graph6_fy1006,Graph6_fex1006,Graph6_fey1006);
   gre->SetName("Graph6");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#33cc99");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#33cc99");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph61006 = new TH1F("Graph_Graph61006","Graph",100,0.09,21.99);
   Graph_Graph61006->SetMinimum(7.434223e-05);
   Graph_Graph61006->SetMaximum(45249.55);
   Graph_Graph61006->SetDirectory(nullptr);
   Graph_Graph61006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph61006->SetLineColor(ci);
   Graph_Graph61006->GetXaxis()->SetLabelFont(42);
   Graph_Graph61006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph61006->GetXaxis()->SetTitleFont(42);
   Graph_Graph61006->GetYaxis()->SetLabelFont(42);
   Graph_Graph61006->GetYaxis()->SetTitleFont(42);
   Graph_Graph61006->GetZaxis()->SetLabelFont(42);
   Graph_Graph61006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph61006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph61006);
   
   gre->Draw("p ");
   
   TF1 *7 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   7->SetRange(0.1,3);
   7->SetName("");
   7->SetTitle("");
   7->SetSavedPoint(0,6374.223);
   7->SetSavedPoint(1,6008.287);
   7->SetSavedPoint(2,5585.487);
   7->SetSavedPoint(3,5133.025);
   7->SetSavedPoint(4,4674.241);
   7->SetSavedPoint(5,4226.479);
   7->SetSavedPoint(6,3801.237);
   7->SetSavedPoint(7,3405.246);
   7->SetSavedPoint(8,3041.721);
   7->SetSavedPoint(9,2711.464);
   7->SetSavedPoint(10,2413.713);
   7->SetSavedPoint(11,2146.764);
   7->SetSavedPoint(12,1908.401);
   7->SetSavedPoint(13,1696.182);
   7->SetSavedPoint(14,1507.626);
   7->SetSavedPoint(15,1340.328);
   7->SetSavedPoint(16,1192.022);
   7->SetSavedPoint(17,1060.616);
   7->SetSavedPoint(18,944.2073);
   7->SetSavedPoint(19,841.0789);
   7->SetSavedPoint(20,749.6959);
   7->SetSavedPoint(21,668.6916);
   7->SetSavedPoint(22,596.8539);
   7->SetSavedPoint(23,533.1109);
   7->SetSavedPoint(24,476.5162);
   7->SetSavedPoint(25,426.2357);
   7->SetSavedPoint(26,381.5346);
   7->SetSavedPoint(27,341.7658);
   7->SetSavedPoint(28,306.3597);
   7->SetSavedPoint(29,274.815);
   7->SetSavedPoint(30,246.69);
   7->SetSavedPoint(31,221.5957);
   7->SetSavedPoint(32,199.1893);
   7->SetSavedPoint(33,179.1684);
   7->SetSavedPoint(34,161.2662);
   7->SetSavedPoint(35,145.2473);
   7->SetSavedPoint(36,130.9034);
   7->SetSavedPoint(37,118.0506);
   7->SetSavedPoint(38,106.526);
   7->SetSavedPoint(39,96.18533);
   7->SetSavedPoint(40,86.90092);
   7->SetSavedPoint(41,78.5594);
   7->SetSavedPoint(42,71.0602);
   7->SetSavedPoint(43,64.31399);
   7->SetSavedPoint(44,58.24137);
   7->SetSavedPoint(45,52.77173);
   7->SetSavedPoint(46,47.84221);
   7->SetSavedPoint(47,43.39682);
   7->SetSavedPoint(48,39.38566);
   7->SetSavedPoint(49,35.76421);
   7->SetSavedPoint(50,32.49274);
   7->SetSavedPoint(51,29.53576);
   7->SetSavedPoint(52,26.86155);
   7->SetSavedPoint(53,24.44175);
   7->SetSavedPoint(54,22.25096);
   7->SetSavedPoint(55,20.26646);
   7->SetSavedPoint(56,18.46787);
   7->SetSavedPoint(57,16.83693);
   7->SetSavedPoint(58,15.35726);
   7->SetSavedPoint(59,14.01414);
   7->SetSavedPoint(60,12.79436);
   7->SetSavedPoint(61,11.68606);
   7->SetSavedPoint(62,10.67854);
   7->SetSavedPoint(63,9.762209);
   7->SetSavedPoint(64,8.928413);
   7->SetSavedPoint(65,8.169361);
   7->SetSavedPoint(66,7.478032);
   7->SetSavedPoint(67,6.848096);
   7->SetSavedPoint(68,6.27384);
   7->SetSavedPoint(69,5.750108);
   7->SetSavedPoint(70,5.272244);
   7->SetSavedPoint(71,4.83604);
   7->SetSavedPoint(72,4.437691);
   7->SetSavedPoint(73,4.073757);
   7->SetSavedPoint(74,3.741125);
   7->SetSavedPoint(75,3.436974);
   7->SetSavedPoint(76,3.158752);
   7->SetSavedPoint(77,2.904144);
   7->SetSavedPoint(78,2.671051);
   7->SetSavedPoint(79,2.457571);
   7->SetSavedPoint(80,2.261975);
   7->SetSavedPoint(81,2.082696);
   7->SetSavedPoint(82,1.918309);
   7->SetSavedPoint(83,1.767519);
   7->SetSavedPoint(84,1.62915);
   7->SetSavedPoint(85,1.50213);
   7->SetSavedPoint(86,1.385486);
   7->SetSavedPoint(87,1.278331);
   7->SetSavedPoint(88,1.179857);
   7->SetSavedPoint(89,1.089328);
   7->SetSavedPoint(90,1.006075);
   7->SetSavedPoint(91,0.9294851);
   7->SetSavedPoint(92,0.8590008);
   7->SetSavedPoint(93,0.7941132);
   7->SetSavedPoint(94,0.7343574);
   7->SetSavedPoint(95,0.6793092);
   7->SetSavedPoint(96,0.6285807);
   7->SetSavedPoint(97,0.5818175);
   7->SetSavedPoint(98,0.5386957);
   7->SetSavedPoint(99,0.4989187);
   7->SetSavedPoint(100,0.4622155);
   7->SetSavedPoint(101,0.1);
   7->SetSavedPoint(102,3);
   7->SetFillColor(19);
   7->SetFillStyle(0);
   7->SetLineWidth(2);
   7->GetXaxis()->SetLabelFont(42);
   7->GetXaxis()->SetTitleOffset(1);
   7->GetXaxis()->SetTitleFont(42);
   7->GetYaxis()->SetLabelFont(42);
   7->GetYaxis()->SetTitleFont(42);
   7->Draw("L SAME");
   
   Double_t Graph7_fx1007[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph7_fy1007[58] = { 12070.77, 10731.25, 9577.817, 8506.139, 7565.991, 6158.631, 4630.332, 3687.145, 2865.502, 2251.088, 1777.067, 1411.768, 1136.04, 917.7103, 742.1308, 615.7913, 513.9156,
   429.5185, 357.0658, 302.0427, 252.2921, 195.2301, 133.8208, 103.9452, 77.51105, 57.53287, 42.48513, 32.25849, 24.54253, 18.84697, 14.53582, 9.818981, 6.010576,
   3.786716, 2.458956, 1.622634, 1.088776, 0.7560574, 0.5258261, 0.3762457, 0.2758947, 0.1635738, 0.08197733, 0.04395659, 0.025843, 0.01516561, 0.009672848, 0.005336402, 0.002579134,
   0.001328672, 0.0007542914, 0.0004556648, 0.0002735856, 0.000172806, 0.0001127897, 7.76134e-05, 4.601638e-05, 2.454833e-05 };
   Double_t Graph7_fex1007[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph7_fey1007[58] = { 935.7014, 595.4804, 507.262, 434.8338, 383.9608, 305.8401, 236.0466, 102.0295, 68.68879, 52.49258, 42.03492, 32.48454, 26.02121, 23.6354, 24.1244, 23.54492, 20.47731,
   16.9635, 14.18724, 12.05974, 9.987422, 7.419664, 5.260317, 4.33207, 3.34215, 2.480425, 1.799966, 1.61277, 1.232831, 0.9473095, 0.7655709, 0.3290876, 0.1897769,
   0.1156855, 0.07375075, 0.04961542, 0.03241044, 0.02370571, 0.01569926, 0.01220149, 0.00922165, 0.004772282, 0.002461132, 0.00138154, 0.0009850135, 0.0005563873, 0.0003530363, 0.0001958412, 9.791482e-05,
   5.272981e-05, 3.210843e-05, 2.06318e-05, 1.333377e-05, 9.056411e-06, 6.375506e-06, 4.715291e-06, 2.704421e-06, 1.677352e-06 };
   gre = new TGraphErrors(58,Graph7_fx1007,Graph7_fy1007,Graph7_fex1007,Graph7_fey1007);
   gre->SetName("Graph7");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(228);
   gre->SetMarkerColor(228);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph71007 = new TH1F("Graph_Graph71007","Graph",100,0.09,21.99);
   Graph_Graph71007->SetMinimum(2.058388e-05);
   Graph_Graph71007->SetMaximum(14307.12);
   Graph_Graph71007->SetDirectory(nullptr);
   Graph_Graph71007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph71007->SetLineColor(ci);
   Graph_Graph71007->GetXaxis()->SetLabelFont(42);
   Graph_Graph71007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph71007->GetXaxis()->SetTitleFont(42);
   Graph_Graph71007->GetYaxis()->SetLabelFont(42);
   Graph_Graph71007->GetYaxis()->SetTitleFont(42);
   Graph_Graph71007->GetZaxis()->SetLabelFont(42);
   Graph_Graph71007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph71007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph71007);
   
   gre->Draw("p ");
   
   TF1 *8 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   8->SetRange(0.1,3);
   8->SetName("");
   8->SetTitle("");
   8->SetSavedPoint(0,1591.762);
   8->SetSavedPoint(1,1504.917);
   8->SetSavedPoint(2,1402.834);
   8->SetSavedPoint(3,1292.127);
   8->SetSavedPoint(4,1178.72);
   8->SetSavedPoint(5,1067.169);
   8->SetSavedPoint(6,960.5936);
   8->SetSavedPoint(7,860.9017);
   8->SetSavedPoint(8,769.0788);
   8->SetSavedPoint(9,685.4609);
   8->SetSavedPoint(10,609.9527);
   8->SetSavedPoint(11,542.1903);
   8->SetSavedPoint(12,481.657);
   8->SetSavedPoint(13,427.7619);
   8->SetSavedPoint(14,379.8918);
   8->SetSavedPoint(15,337.4439);
   8->SetSavedPoint(16,299.8452);
   8->SetSavedPoint(17,266.5638);
   8->SetSavedPoint(18,237.1131);
   8->SetSavedPoint(19,211.0535);
   8->SetSavedPoint(20,187.9905);
   8->SetSavedPoint(21,167.5728);
   8->SetSavedPoint(22,149.4886);
   8->SetSavedPoint(23,133.4621);
   8->SetSavedPoint(24,119.2502);
   8->SetSavedPoint(25,106.6385);
   8->SetSavedPoint(26,95.43842);
   8->SetSavedPoint(27,85.48432);
   8->SetSavedPoint(28,76.63048);
   8->SetSavedPoint(29,68.74884);
   8->SetSavedPoint(30,61.72688);
   8->SetSavedPoint(31,55.46564);
   8->SetSavedPoint(32,49.87808);
   8->SetSavedPoint(33,44.8876);
   8->SetSavedPoint(34,40.42675);
   8->SetSavedPoint(35,36.43608);
   8->SetSavedPoint(36,32.86317);
   8->SetSavedPoint(37,29.66175);
   8->SetSavedPoint(38,26.79095);
   8->SetSavedPoint(39,24.21466);
   8->SetSavedPoint(40,21.9009);
   8->SetSavedPoint(41,19.82138);
   8->SetSavedPoint(42,17.95101);
   8->SetSavedPoint(43,16.26755);
   8->SetSavedPoint(44,14.75124);
   8->SetSavedPoint(45,13.38455);
   8->SetSavedPoint(46,12.15186);
   8->SetSavedPoint(47,11.0393);
   8->SetSavedPoint(48,10.03449);
   8->SetSavedPoint(49,9.126413);
   8->SetSavedPoint(50,8.305231);
   8->SetSavedPoint(51,7.562165);
   8->SetSavedPoint(52,6.889372);
   8->SetSavedPoint(53,6.279837);
   8->SetSavedPoint(54,5.727283);
   8->SetSavedPoint(55,5.226092);
   8->SetSavedPoint(56,4.771227);
   8->SetSavedPoint(57,4.358172);
   8->SetSavedPoint(58,3.982876);
   8->SetSavedPoint(59,3.641699);
   8->SetSavedPoint(60,3.331373);
   8->SetSavedPoint(61,3.048957);
   8->SetSavedPoint(62,2.791807);
   8->SetSavedPoint(63,2.557541);
   8->SetSavedPoint(64,2.344014);
   8->SetSavedPoint(65,2.149293);
   8->SetSavedPoint(66,1.971633);
   8->SetSavedPoint(67,1.809461);
   8->SetSavedPoint(68,1.661355);
   8->SetSavedPoint(69,1.526031);
   8->SetSavedPoint(70,1.402329);
   8->SetSavedPoint(71,1.289197);
   8->SetSavedPoint(72,1.185685);
   8->SetSavedPoint(73,1.090934);
   8->SetSavedPoint(74,1.004162);
   8->SetSavedPoint(75,0.9246628);
   8->SetSavedPoint(76,0.8517957);
   8->SetSavedPoint(77,0.7849786);
   8->SetSavedPoint(78,0.7236833);
   8->SetSavedPoint(79,0.6674301);
   8->SetSavedPoint(80,0.6157827);
   8->SetSavedPoint(81,0.5683449);
   8->SetSavedPoint(82,0.5247559);
   8->SetSavedPoint(83,0.4846876);
   8->SetSavedPoint(84,0.447841);
   8->SetSavedPoint(85,0.4139439);
   8->SetSavedPoint(86,0.3827482);
   8->SetSavedPoint(87,0.3540277);
   8->SetSavedPoint(88,0.327576);
   8->SetSavedPoint(89,0.3032049);
   8->SetSavedPoint(90,0.2807424);
   8->SetSavedPoint(91,0.2600315);
   8->SetSavedPoint(92,0.2409287);
   8->SetSavedPoint(93,0.2233029);
   8->SetSavedPoint(94,0.2070341);
   8->SetSavedPoint(95,0.1920126);
   8->SetSavedPoint(96,0.178138);
   8->SetSavedPoint(97,0.1653184);
   8->SetSavedPoint(98,0.1534694);
   8->SetSavedPoint(99,0.142514);
   8->SetSavedPoint(100,0.1323813);
   8->SetSavedPoint(101,0.1);
   8->SetSavedPoint(102,3);
   8->SetFillColor(19);
   8->SetFillStyle(0);
   8->SetLineWidth(2);
   8->GetXaxis()->SetLabelFont(42);
   8->GetXaxis()->SetTitleOffset(1);
   8->GetXaxis()->SetTitleFont(42);
   8->GetYaxis()->SetLabelFont(42);
   8->GetYaxis()->SetTitleFont(42);
   8->Draw("L SAME");
   
   Double_t Graph8_fx1008[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph8_fy1008[58] = { 3257.873, 2926.492, 2617.271, 2307.11, 2036.111, 1634.5, 1233.144, 957.2411, 741.6705, 579.0634, 451.3969, 356.9533, 285.1924, 230.5603, 185.1158, 155.8867, 130.3173,
   107.2237, 89.60987, 74.72333, 62.63555, 47.62158, 33.26809, 25.32423, 18.78905, 13.99194, 10.445, 7.876337, 5.936352, 4.602382, 3.538822, 2.437223, 1.491462,
   0.9541046, 0.621737, 0.410308, 0.2831685, 0.1959091, 0.1395471, 0.09847303, 0.07442248, 0.04313676, 0.02283307, 0.01196457, 0.007177971, 0.004190893, 0.002663579, 0.001455567, 0.0006874295,
   0.0003529956, 0.0001976868, 0.00011348, 7.038468e-05, 4.533299e-05, 3.00344e-05, 2.092713e-05, 1.205054e-05, 5.594749e-06 };
   Double_t Graph8_fex1008[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph8_fey1008[58] = { 248.7077, 152.4087, 128.8603, 108.6298, 94.94748, 72.86756, 56.92473, 32.51211, 24.01975, 18.67408, 15.22644, 11.8355, 9.681758, 8.249492, 7.581793, 7.664375, 6.759144,
   5.56256, 4.632962, 4.07321, 3.296633, 2.380563, 1.729378, 1.397465, 1.073375, 0.7796915, 0.5645528, 0.48399, 0.3592427, 0.2803673, 0.2255593, 0.1152221, 0.07236651,
   0.04173078, 0.02593693, 0.01676005, 0.01256392, 0.008536878, 0.005732052, 0.004543951, 0.003510681, 0.001661742, 0.0008987141, 0.0004575853, 0.000340276, 0.0001835176, 0.0001150367, 6.291637e-05, 3.130701e-05,
   1.688932e-05, 9.932724e-06, 6.154508e-06, 4.141125e-06, 3.458571e-06, 2.453735e-06, 1.826861e-06, 1.024239e-06, 5.658813e-07 };
   gre = new TGraphErrors(58,Graph8_fx1008,Graph8_fy1008,Graph8_fex1008,Graph8_fey1008);
   gre->SetName("Graph8");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#6699ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#6699ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph81008 = new TH1F("Graph_Graph81008","Graph",100,0.09,21.99);
   Graph_Graph81008->SetMinimum(4.525981e-06);
   Graph_Graph81008->SetMaximum(3857.238);
   Graph_Graph81008->SetDirectory(nullptr);
   Graph_Graph81008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph81008->SetLineColor(ci);
   Graph_Graph81008->GetXaxis()->SetLabelFont(42);
   Graph_Graph81008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph81008->GetXaxis()->SetTitleFont(42);
   Graph_Graph81008->GetYaxis()->SetLabelFont(42);
   Graph_Graph81008->GetYaxis()->SetTitleFont(42);
   Graph_Graph81008->GetZaxis()->SetLabelFont(42);
   Graph_Graph81008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph81008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph81008);
   
   gre->Draw("p ");
   
   TF1 *9 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   9->SetRange(0.1,3);
   9->SetName("");
   9->SetTitle("");
   9->SetSavedPoint(0,351.544);
   9->SetSavedPoint(1,334.1641);
   9->SetSavedPoint(2,313.1159);
   9->SetSavedPoint(3,289.7567);
   9->SetSavedPoint(4,265.3912);
   9->SetSavedPoint(5,241.078);
   9->SetSavedPoint(6,217.5818);
   9->SetSavedPoint(7,195.4005);
   9->SetSavedPoint(8,174.8196);
   9->SetSavedPoint(9,155.9682);
   9->SetSavedPoint(10,138.867);
   9->SetSavedPoint(11,123.4658);
   9->SetSavedPoint(12,109.6713);
   9->SetSavedPoint(13,97.36618);
   9->SetSavedPoint(14,86.42287);
   9->SetSavedPoint(15,76.71204);
   9->SetSavedPoint(16,68.10825);
   9->SetSavedPoint(17,60.49323);
   9->SetSavedPoint(18,53.75761);
   9->SetSavedPoint(19,47.80167);
   9->SetSavedPoint(20,42.53541);
   9->SetSavedPoint(21,37.87821);
   9->SetSavedPoint(22,33.75829);
   9->SetSavedPoint(23,30.11196);
   9->SetSavedPoint(24,26.88294);
   9->SetSavedPoint(25,24.02159);
   9->SetSavedPoint(26,21.4842);
   9->SetSavedPoint(27,19.23235);
   9->SetSavedPoint(28,17.23225);
   9->SetSavedPoint(29,15.45425);
   9->SetSavedPoint(30,13.87231);
   9->SetSavedPoint(31,12.46354);
   9->SetSavedPoint(32,11.20787);
   9->SetSavedPoint(33,10.08762);
   9->SetSavedPoint(34,9.0873);
   9->SetSavedPoint(35,8.193243);
   9->SetSavedPoint(36,7.393441);
   9->SetSavedPoint(37,6.677311);
   9->SetSavedPoint(38,6.035527);
   9->SetSavedPoint(39,5.459862);
   9->SetSavedPoint(40,4.943051);
   9->SetSavedPoint(41,4.478678);
   9->SetSavedPoint(42,4.061064);
   9->SetSavedPoint(43,3.685187);
   9->SetSavedPoint(44,3.346594);
   9->SetSavedPoint(45,3.041338);
   9->SetSavedPoint(46,2.765916);
   9->SetSavedPoint(47,2.517216);
   9->SetSavedPoint(48,2.29247);
   9->SetSavedPoint(49,2.089215);
   9->SetSavedPoint(50,1.905259);
   9->SetSavedPoint(51,1.738646);
   9->SetSavedPoint(52,1.587631);
   9->SetSavedPoint(53,1.450656);
   9->SetSavedPoint(54,1.326328);
   9->SetSavedPoint(55,1.213402);
   9->SetSavedPoint(56,1.110762);
   9->SetSavedPoint(57,1.01741);
   9->SetSavedPoint(58,0.9324479);
   9->SetSavedPoint(59,0.8550732);
   9->SetSavedPoint(60,0.7845631);
   9->SetSavedPoint(61,0.7202685);
   9->SetSavedPoint(62,0.6616055);
   9->SetSavedPoint(63,0.6080484);
   9->SetSavedPoint(64,0.5591238);
   9->SetSavedPoint(65,0.5144049);
   9->SetSavedPoint(66,0.4735065);
   9->SetSavedPoint(67,0.4360811);
   9->SetSavedPoint(68,0.4018146);
   9->SetSavedPoint(69,0.3704231);
   9->SetSavedPoint(70,0.3416499);
   9->SetSavedPoint(71,0.3152626);
   9->SetSavedPoint(72,0.2910505);
   9->SetSavedPoint(73,0.2688229);
   9->SetSavedPoint(74,0.2484068);
   9->SetSavedPoint(75,0.229645);
   9->SetSavedPoint(76,0.212395);
   9->SetSavedPoint(77,0.1965272);
   9->SetSavedPoint(78,0.1819239);
   9->SetSavedPoint(79,0.1684778);
   9->SetSavedPoint(80,0.1560916);
   9->SetSavedPoint(81,0.1446763);
   9->SetSavedPoint(82,0.1341512);
   9->SetSavedPoint(83,0.1244424);
   9->SetSavedPoint(84,0.1154825);
   9->SetSavedPoint(85,0.1072104);
   9->SetSavedPoint(86,0.09956974);
   9->SetSavedPoint(87,0.09250944);
   9->SetSavedPoint(88,0.08598264);
   9->SetSavedPoint(89,0.07994652);
   9->SetSavedPoint(90,0.0743619);
   9->SetSavedPoint(91,0.06919291);
   9->SetSavedPoint(92,0.0644067);
   9->SetSavedPoint(93,0.05997317);
   9->SetSavedPoint(94,0.05586472);
   9->SetSavedPoint(95,0.05205605);
   9->SetSavedPoint(96,0.04852394);
   9->SetSavedPoint(97,0.04524707);
   9->SetSavedPoint(98,0.04220585);
   9->SetSavedPoint(99,0.03938231);
   9->SetSavedPoint(100,0.0367599);
   9->SetSavedPoint(101,0.1);
   9->SetSavedPoint(102,3);
   9->SetFillColor(19);
   9->SetFillStyle(0);
   9->SetLineWidth(2);
   9->GetXaxis()->SetLabelFont(42);
   9->GetXaxis()->SetTitleOffset(1);
   9->GetXaxis()->SetTitleFont(42);
   9->GetYaxis()->SetLabelFont(42);
   9->GetYaxis()->SetTitleFont(42);
   9->Draw("L SAME");
   
   Double_t Graph9_fx1009[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph9_fy1009[58] = { 811.8986, 725.0609, 637.7827, 575.9012, 496.8717, 398.507, 298.1325, 229.9862, 171.5003, 134.4062, 105.7539, 82.59081, 65.57516, 52.49414, 42.2923, 35.46104, 28.72757,
   23.61281, 19.87709, 16.4186, 13.77058, 10.41668, 7.069026, 5.5664, 4.102566, 3.093533, 2.281399, 1.666169, 1.277314, 0.9916815, 0.7615278, 0.5205731, 0.3290272,
   0.2134204, 0.1409099, 0.09452706, 0.06483664, 0.04502638, 0.03233264, 0.02382162, 0.01735295, 0.01036836, 0.005220014, 0.002890133, 0.00167751, 0.001008283, 0.0006306403, 0.0003419073, 0.0001592898,
   8.261448e-05, 4.723719e-05, 2.663064e-05, 1.550602e-05, 1.043585e-05, 6.133502e-06, 3.96035e-06, 2.328605e-06, 1.171514e-06 };
   Double_t Graph9_fex1009[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph9_fey1009[58] = { 65.62508, 40.56022, 33.72048, 29.20812, 24.92092, 18.83551, 14.55836, 8.222463, 8.138547, 4.581356, 3.773319, 2.905484, 2.3692, 1.984298, 1.827599, 1.797147, 1.536398,
   1.273044, 1.074245, 0.9359701, 0.7633051, 0.5439971, 0.385858, 0.3210662, 0.2485892, 0.184877, 0.131142, 0.1069984, 0.08174489, 0.06441835, 0.05196711, 0.02690919, 0.01745988,
   0.01028228, 0.006529455, 0.004439347, 0.003277278, 0.002260425, 0.001565321, 0.001350047, 0.0009981872, 0.0004940589, 0.0002608077, 0.0001392415, 0.0001060177, 5.529119e-05, 3.448367e-05, 1.856434e-05, 9.183802e-06,
   5.03908e-06, 3.056175e-06, 1.87774e-06, 1.210769e-06, 1.0143e-06, 6.643676e-07, 4.697761e-07, 2.683015e-07, 1.612357e-07 };
   gre = new TGraphErrors(58,Graph9_fx1009,Graph9_fy1009,Graph9_fex1009,Graph9_fey1009);
   gre->SetName("Graph9");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#3399ff");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#3399ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph91009 = new TH1F("Graph_Graph91009","Graph",100,0.09,21.99);
   Graph_Graph91009->SetMinimum(9.092508e-07);
   Graph_Graph91009->SetMaximum(965.276);
   Graph_Graph91009->SetDirectory(nullptr);
   Graph_Graph91009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph91009->SetLineColor(ci);
   Graph_Graph91009->GetXaxis()->SetLabelFont(42);
   Graph_Graph91009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph91009->GetXaxis()->SetTitleFont(42);
   Graph_Graph91009->GetYaxis()->SetLabelFont(42);
   Graph_Graph91009->GetYaxis()->SetTitleFont(42);
   Graph_Graph91009->GetZaxis()->SetLabelFont(42);
   Graph_Graph91009->GetZaxis()->SetTitleOffset(1);
   Graph_Graph91009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph91009);
   
   gre->Draw("p ");
   
   TF1 *10 = new TF1("*",0.1,3,0);
    //The original function :  had originally been created by:
    //TF1 * = new TF1("",,0.1,3,0, 1, TF1::EAddToList::kDefault);
   10->SetRange(0.1,3);
   10->SetName("");
   10->SetTitle("");
   10->SetSavedPoint(0,67.83554);
   10->SetSavedPoint(1,64.66152);
   10->SetSavedPoint(2,60.73891);
   10->SetSavedPoint(3,56.3203);
   10->SetSavedPoint(4,51.65993);
   10->SetSavedPoint(5,46.97075);
   10->SetSavedPoint(6,42.41088);
   10->SetSavedPoint(7,38.08642);
   10->SetSavedPoint(8,34.06075);
   10->SetSavedPoint(9,30.3651);
   10->SetSavedPoint(10,27.0079);
   10->SetSavedPoint(11,23.98237);
   10->SetSavedPoint(12,21.27218);
   10->SetSavedPoint(13,18.85554);
   10->SetSavedPoint(14,16.70803);
   10->SetSavedPoint(15,14.80452);
   10->SetSavedPoint(16,13.12037);
   10->SetSavedPoint(17,11.63218);
   10->SetSavedPoint(18,10.31823);
   10->SetSavedPoint(19,9.158657);
   10->SetSavedPoint(20,8.135483);
   10->SetSavedPoint(21,7.2326);
   10->SetSavedPoint(22,6.435651);
   10->SetSavedPoint(23,5.731908);
   10->SetSavedPoint(24,5.110126);
   10->SetSavedPoint(25,4.560398);
   10->SetSavedPoint(26,4.074011);
   10->SetSavedPoint(27,3.643317);
   10->SetSavedPoint(28,3.261609);
   10->SetSavedPoint(29,2.923004);
   10->SetSavedPoint(30,2.622352);
   10->SetSavedPoint(31,2.355138);
   10->SetSavedPoint(32,2.117405);
   10->SetSavedPoint(33,1.905688);
   10->SetSavedPoint(34,1.716947);
   10->SetSavedPoint(35,1.548516);
   10->SetSavedPoint(36,1.398053);
   10->SetSavedPoint(37,1.263503);
   10->SetSavedPoint(38,1.14306);
   10->SetSavedPoint(39,1.035132);
   10->SetSavedPoint(40,0.9383221);
   10->SetSavedPoint(41,0.8513957);
   10->SetSavedPoint(42,0.7732653);
   10->SetSavedPoint(43,0.702971);
   10->SetSavedPoint(44,0.6396642);
   10->SetSavedPoint(45,0.5825948);
   10->SetSavedPoint(46,0.5310984);
   10->SetSavedPoint(47,0.4845864);
   10->SetSavedPoint(48,0.4425368);
   10->SetSavedPoint(49,0.404486);
   10->SetSavedPoint(50,0.3700221);
   10->SetSavedPoint(51,0.3387787);
   10->SetSavedPoint(52,0.3104295);
   10->SetSavedPoint(53,0.2846838);
   10->SetSavedPoint(54,0.2612821);
   10->SetSavedPoint(55,0.2399927);
   10->SetSavedPoint(56,0.2206087);
   10->SetSavedPoint(57,0.2029449);
   10->SetSavedPoint(58,0.1868353);
   10->SetSavedPoint(59,0.1721314);
   10->SetSavedPoint(60,0.1586998);
   10->SetSavedPoint(61,0.1464208);
   10->SetSavedPoint(62,0.1351868);
   10->SetSavedPoint(63,0.1249011);
   10->SetSavedPoint(64,0.1154766);
   10->SetSavedPoint(65,0.1068348);
   10->SetSavedPoint(66,0.09890486);
   10->SetSavedPoint(67,0.09162301);
   10->SetSavedPoint(68,0.08493155);
   10->SetSavedPoint(69,0.07877832);
   10->SetSavedPoint(70,0.07311617);
   10->SetSavedPoint(71,0.06790238);
   10->SetSavedPoint(72,0.06309827);
   10->SetSavedPoint(73,0.05866873);
   10->SetSavedPoint(74,0.05458193);
   10->SetSavedPoint(75,0.05080895);
   10->SetSavedPoint(76,0.04732352);
   10->SetSavedPoint(77,0.04410172);
   10->SetSavedPoint(78,0.04112181);
   10->SetSavedPoint(79,0.03836397);
   10->SetSavedPoint(80,0.03581014);
   10->SetSavedPoint(81,0.03344386);
   10->SetSavedPoint(82,0.03125008);
   10->SetSavedPoint(83,0.0292151);
   10->SetSavedPoint(84,0.02732634);
   10->SetSavedPoint(85,0.02557235);
   10->SetSavedPoint(86,0.02394263);
   10->SetSavedPoint(87,0.02242755);
   10->SetSavedPoint(88,0.02101832);
   10->SetSavedPoint(89,0.01970684);
   10->SetSavedPoint(90,0.01848573);
   10->SetSavedPoint(91,0.01734817);
   10->SetSavedPoint(92,0.01628791);
   10->SetSavedPoint(93,0.01529923);
   10->SetSavedPoint(94,0.01437683);
   10->SetSavedPoint(95,0.01351586);
   10->SetSavedPoint(96,0.01271185);
   10->SetSavedPoint(97,0.01196068);
   10->SetSavedPoint(98,0.01125856);
   10->SetSavedPoint(99,0.01060198);
   10->SetSavedPoint(100,0.009987708);
   10->SetSavedPoint(101,0.1);
   10->SetSavedPoint(102,3);
   10->SetFillColor(19);
   10->SetFillStyle(0);
   10->SetLineWidth(2);
   10->GetXaxis()->SetLabelFont(42);
   10->GetXaxis()->SetTitleOffset(1);
   10->GetXaxis()->SetTitleFont(42);
   10->GetYaxis()->SetLabelFont(42);
   10->GetYaxis()->SetTitleFont(42);
   10->Draw("L SAME");
   
   Double_t Graph10_fx1010[58] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775,
   0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3,
   2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7, 3.9, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.5, 8.5,
   9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 17, 19 };
   Double_t Graph10_fy1010[58] = { 160.0751, 141.8389, 125.7918, 112.8315, 100.3849, 82.35596, 60.27979, 46.72397, 35.38927, 26.65265, 20.59431, 16.06101, 12.49989, 10.15393, 8.069887, 6.667999, 5.510006,
   4.497777, 3.777156, 3.108907, 2.601261, 1.864144, 1.240246, 1.031731, 0.7367341, 0.5436733, 0.3872579, 0.2859002, 0.2290412, 0.1698742, 0.1304418, 0.09076985, 0.05889286,
   0.0377541, 0.02450043, 0.01657648, 0.01140165, 0.008058642, 0.005794149, 0.004163321, 0.003048429, 0.001920045, 0.0009637217, 0.0005189361, 0.000300562, 0.0001804741, 0.0001133372, 6.048822e-05, 2.829288e-05,
   1.413162e-05, 7.938952e-06, 4.478925e-06, 2.58544e-06, 1.701661e-06, 1.016748e-06, 6.474218e-07, 4.454092e-07, 1.754759e-07 };
   Double_t Graph10_fex1010[58] = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025,
   0.025, 0.025, 0.025, 0.025, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1,
   0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.5,
   0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1 };
   Double_t Graph10_fey1010[58] = { 14.20409, 8.707636, 7.297954, 6.285047, 5.523648, 4.127899, 3.126405, 1.786649, 1.304476, 0.9797953, 0.796351, 0.6186004, 0.4971502, 0.4208209, 0.3792839, 0.3565483, 0.3127405,
   0.2590641, 0.2197597, 0.191242, 0.1570035, 0.1048513, 0.07346869, 0.06516542, 0.04926777, 0.03625045, 0.02481544, 0.02038997, 0.01645244, 0.01247844, 0.01007204, 0.005233439, 0.003537447,
   0.002168352, 0.001400776, 0.0009848947, 0.0007286832, 0.0005269283, 0.0003880998, 0.0003036384, 0.0002430761, 0.0001249812, 6.568442e-05, 3.930042e-05, 2.783512e-05, 1.392496e-05, 8.508164e-06, 4.945602e-06, 2.327182e-06,
   1.250167e-06, 7.5762e-07, 4.754276e-07, 3.074924e-07, 2.449383e-07, 1.6388e-07, 1.179336e-07, 7.629626e-08, 3.991807e-08 };
   gre = new TGraphErrors(58,Graph10_fx1010,Graph10_fy1010,Graph10_fex1010,Graph10_fey1010);
   gre->SetName("Graph10");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#006699");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#006699");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph101010 = new TH1F("Graph_Graph101010","Graph",100,0.09,21.99);
   Graph_Graph101010->SetMinimum(1.22002e-07);
   Graph_Graph101010->SetMaximum(191.7072);
   Graph_Graph101010->SetDirectory(nullptr);
   Graph_Graph101010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph101010->SetLineColor(ci);
   Graph_Graph101010->GetXaxis()->SetLabelFont(42);
   Graph_Graph101010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph101010->GetXaxis()->SetTitleFont(42);
   Graph_Graph101010->GetYaxis()->SetLabelFont(42);
   Graph_Graph101010->GetYaxis()->SetTitleFont(42);
   Graph_Graph101010->GetZaxis()->SetLabelFont(42);
   Graph_Graph101010->GetZaxis()->SetTitleOffset(1);
   Graph_Graph101010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph101010);
   
   gre->Draw("p ");
   
   TPaveText *pt = new TPaveText(0.4398567,0.9344958,0.5601433,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Graph");
   pt->Draw();
   c1->Modified();
   c1->SetSelected(c1);
}
