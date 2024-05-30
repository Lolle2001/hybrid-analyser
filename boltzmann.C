#ifdef __CLING__
#pragma cling optimize(0)
#endif
void c1()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu May 30 14:53:33 2024) by ROOT version 6.30/02
   TCanvas *c1 = new TCanvas("c1", "c1",10,64,700,500);
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
   1->SetSavedPoint(0,5110703);
   1->SetSavedPoint(1,4653085);
   1->SetSavedPoint(2,4192855);
   1->SetSavedPoint(3,3753036);
   1->SetSavedPoint(4,3345557);
   1->SetSavedPoint(5,2975206);
   1->SetSavedPoint(6,2642594);
   1->SetSavedPoint(7,2346089);
   1->SetSavedPoint(8,2082972);
   1->SetSavedPoint(9,1850109);
   1->SetSavedPoint(10,1644321);
   1->SetSavedPoint(11,1462574);
   1->SetSavedPoint(12,1302069);
   1->SetSavedPoint(13,1160278);
   1->SetSavedPoint(14,1034948);
   1->SetSavedPoint(15,924081.4);
   1->SetSavedPoint(16,825923.5);
   1->SetSavedPoint(17,738933);
   1->SetSavedPoint(18,661760.6);
   1->SetSavedPoint(19,593226.3);
   1->SetSavedPoint(20,532297.9);
   1->SetSavedPoint(21,478073.3);
   1->SetSavedPoint(22,429763.1);
   1->SetSavedPoint(23,386676.7);
   1->SetSavedPoint(24,348209);
   1->SetSavedPoint(25,313829.6);
   1->SetSavedPoint(26,283073.1);
   1->SetSavedPoint(27,255530.6);
   1->SetSavedPoint(28,230842.7);
   1->SetSavedPoint(29,208692.8);
   1->SetSavedPoint(30,188801.9);
   1->SetSavedPoint(31,170923.9);
   1->SetSavedPoint(32,154841.3);
   1->SetSavedPoint(33,140361.7);
   1->SetSavedPoint(34,127314.9);
   1->SetSavedPoint(35,115549.9);
   1->SetSavedPoint(36,104932.7);
   1->SetSavedPoint(37,95344.25);
   1->SetSavedPoint(38,86678.8);
   1->SetSavedPoint(39,78842.08);
   1->SetSavedPoint(40,71750.12);
   1->SetSavedPoint(41,65328);
   1->SetSavedPoint(42,59508.82);
   1->SetSavedPoint(43,54232.79);
   1->SetSavedPoint(44,49446.41);
   1->SetSavedPoint(45,45101.79);
   1->SetSavedPoint(46,41155.98);
   1->SetSavedPoint(47,37570.49);
   1->SetSavedPoint(48,34310.72);
   1->SetSavedPoint(49,31345.61);
   1->SetSavedPoint(50,28647.22);
   1->SetSavedPoint(51,26190.42);
   1->SetSavedPoint(52,23952.56);
   1->SetSavedPoint(53,21913.23);
   1->SetSavedPoint(54,20054.03);
   1->SetSavedPoint(55,18358.35);
   1->SetSavedPoint(56,16811.18);
   1->SetSavedPoint(57,15398.97);
   1->SetSavedPoint(58,14109.46);
   1->SetSavedPoint(59,12931.56);
   1->SetSavedPoint(60,11855.22);
   1->SetSavedPoint(61,10871.35);
   1->SetSavedPoint(62,9971.698);
   1->SetSavedPoint(63,9148.792);
   1->SetSavedPoint(64,8395.845);
   1->SetSavedPoint(65,7706.696);
   1->SetSavedPoint(66,7075.75);
   1->SetSavedPoint(67,6497.924);
   1->SetSavedPoint(68,5968.595);
   1->SetSavedPoint(69,5483.558);
   1->SetSavedPoint(70,5038.989);
   1->SetSavedPoint(71,4631.404);
   1->SetSavedPoint(72,4257.631);
   1->SetSavedPoint(73,3914.78);
   1->SetSavedPoint(74,3600.217);
   1->SetSavedPoint(75,3311.54);
   1->SetSavedPoint(76,3046.558);
   1->SetSavedPoint(77,2803.271);
   1->SetSavedPoint(78,2579.854);
   1->SetSavedPoint(79,2374.641);
   1->SetSavedPoint(80,2186.109);
   1->SetSavedPoint(81,2012.868);
   1->SetSavedPoint(82,1853.644);
   1->SetSavedPoint(83,1707.277);
   1->SetSavedPoint(84,1572.703);
   1->SetSavedPoint(85,1448.947);
   1->SetSavedPoint(86,1335.121);
   1->SetSavedPoint(87,1230.409);
   1->SetSavedPoint(88,1134.065);
   1->SetSavedPoint(89,1045.405);
   1->SetSavedPoint(90,963.8029);
   1->SetSavedPoint(91,888.6846);
   1->SetSavedPoint(92,819.5241);
   1->SetSavedPoint(93,755.8392);
   1->SetSavedPoint(94,697.1874);
   1->SetSavedPoint(95,643.1631);
   1->SetSavedPoint(96,593.3939);
   1->SetSavedPoint(97,547.5382);
   1->SetSavedPoint(98,505.2825);
   1->SetSavedPoint(99,466.3388);
   1->SetSavedPoint(100,430.4428);
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
   2->SetSavedPoint(0,2121537);
   2->SetSavedPoint(1,1930206);
   2->SetSavedPoint(2,1737904);
   2->SetSavedPoint(3,1554253);
   2->SetSavedPoint(4,1384225);
   2->SetSavedPoint(5,1229800);
   2->SetSavedPoint(6,1091216);
   2->SetSavedPoint(7,967772.5);
   2->SetSavedPoint(8,858318.4);
   2->SetSavedPoint(9,761531.6);
   2->SetSavedPoint(10,676073);
   2->SetSavedPoint(11,600665.8);
   2->SetSavedPoint(12,534133.9);
   2->SetSavedPoint(13,475415.4);
   2->SetSavedPoint(14,423563.5);
   2->SetSavedPoint(15,377741.4);
   2->SetSavedPoint(16,337212.6);
   2->SetSavedPoint(17,301331.6);
   2->SetSavedPoint(18,269533.3);
   2->SetSavedPoint(19,241324);
   2->SetSavedPoint(20,216272);
   2->SetSavedPoint(21,194000.3);
   2->SetSavedPoint(22,174179.4);
   2->SetSavedPoint(23,156521);
   2->SetSavedPoint(24,140773);
   2->SetSavedPoint(25,126714.3);
   2->SetSavedPoint(26,114151.1);
   2->SetSavedPoint(27,102913.5);
   2->SetSavedPoint(28,92852.07);
   2->SetSavedPoint(29,83835.27);
   2->SetSavedPoint(30,75747.38);
   2->SetSavedPoint(31,68486.36);
   2->SetSavedPoint(32,61962.12);
   2->SetSavedPoint(33,56095.06);
   2->SetSavedPoint(34,50814.76);
   2->SetSavedPoint(35,46058.86);
   2->SetSavedPoint(36,41772.06);
   2->SetSavedPoint(37,37905.27);
   2->SetSavedPoint(38,34414.88);
   2->SetSavedPoint(39,31262.11);
   2->SetSavedPoint(40,28412.42);
   2->SetSavedPoint(41,25835.03);
   2->SetSavedPoint(42,23502.47);
   2->SetSavedPoint(43,21390.23);
   2->SetSavedPoint(44,19476.38);
   2->SetSavedPoint(45,17741.32);
   2->SetSavedPoint(46,16167.49);
   2->SetSavedPoint(47,14739.16);
   2->SetSavedPoint(48,13442.21);
   2->SetSavedPoint(49,12263.99);
   2->SetSavedPoint(50,11193.1);
   2->SetSavedPoint(51,10219.32);
   2->SetSavedPoint(52,9333.452);
   2->SetSavedPoint(53,8527.201);
   2->SetSavedPoint(54,7793.103);
   2->SetSavedPoint(55,7124.429);
   2->SetSavedPoint(56,6515.106);
   2->SetSavedPoint(57,5959.651);
   2->SetSavedPoint(58,5453.113);
   2->SetSavedPoint(59,4991.018);
   2->SetSavedPoint(60,4569.315);
   2->SetSavedPoint(61,4184.344);
   2->SetSavedPoint(62,3832.788);
   2->SetSavedPoint(63,3511.643);
   2->SetSavedPoint(64,3218.186);
   2->SetSavedPoint(65,2949.948);
   2->SetSavedPoint(66,2704.689);
   2->SetSavedPoint(67,2480.376);
   2->SetSavedPoint(68,2275.161);
   2->SetSavedPoint(69,2087.369);
   2->SetSavedPoint(70,1915.474);
   2->SetSavedPoint(71,1758.089);
   2->SetSavedPoint(72,1613.953);
   2->SetSavedPoint(73,1481.919);
   2->SetSavedPoint(74,1360.941);
   2->SetSavedPoint(75,1250.068);
   2->SetSavedPoint(76,1148.433);
   2->SetSavedPoint(77,1055.244);
   2->SetSavedPoint(78,969.783);
   2->SetSavedPoint(79,891.3911);
   2->SetSavedPoint(80,819.4691);
   2->SetSavedPoint(81,753.4698);
   2->SetSavedPoint(82,692.8936);
   2->SetSavedPoint(83,637.2842);
   2->SetSavedPoint(84,586.2248);
   2->SetSavedPoint(85,539.3346);
   2->SetSavedPoint(86,496.2655);
   2->SetSavedPoint(87,456.6992);
   2->SetSavedPoint(88,420.3446);
   2->SetSavedPoint(89,386.9354);
   2->SetSavedPoint(90,356.2281);
   2->SetSavedPoint(91,327.9995);
   2->SetSavedPoint(92,302.0457);
   2->SetSavedPoint(93,278.1795);
   2->SetSavedPoint(94,256.23);
   2->SetSavedPoint(95,236.04);
   2->SetSavedPoint(96,217.4661);
   2->SetSavedPoint(97,200.3764);
   2->SetSavedPoint(98,184.6501);
   2->SetSavedPoint(99,170.1766);
   2->SetSavedPoint(100,156.8543);
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
   3->SetSavedPoint(0,790042.2);
   3->SetSavedPoint(1,718824.9);
   3->SetSavedPoint(2,647269.9);
   3->SetSavedPoint(3,578953);
   3->SetSavedPoint(4,515716);
   3->SetSavedPoint(5,458288.7);
   3->SetSavedPoint(6,406753.5);
   3->SetSavedPoint(7,360845.7);
   3->SetSavedPoint(8,320134.7);
   3->SetSavedPoint(9,284127.9);
   3->SetSavedPoint(10,252326.8);
   3->SetSavedPoint(11,224257.4);
   3->SetSavedPoint(12,199482.9);
   3->SetSavedPoint(13,177609.6);
   3->SetSavedPoint(14,158286.5);
   3->SetSavedPoint(15,141203.5);
   3->SetSavedPoint(16,126087.7);
   3->SetSavedPoint(17,112699.9);
   3->SetSavedPoint(18,100830.6);
   3->SetSavedPoint(19,90296.82);
   3->SetSavedPoint(20,80938.52);
   3->SetSavedPoint(21,72615.82);
   3->SetSavedPoint(22,65206.43);
   3->SetSavedPoint(23,58603.32);
   3->SetSavedPoint(24,52712.77);
   3->SetSavedPoint(25,47452.66);
   3->SetSavedPoint(26,42750.94);
   3->SetSavedPoint(27,38544.31);
   3->SetSavedPoint(28,34777.14);
   3->SetSavedPoint(29,31400.48);
   3->SetSavedPoint(30,28371.18);
   3->SetSavedPoint(31,25651.18);
   3->SetSavedPoint(32,23206.87);
   3->SetSavedPoint(33,21008.54);
   3->SetSavedPoint(34,19029.88);
   3->SetSavedPoint(35,17247.61);
   3->SetSavedPoint(36,15641.05);
   3->SetSavedPoint(37,14191.84);
   3->SetSavedPoint(38,12883.68);
   3->SetSavedPoint(39,11702.05);
   3->SetSavedPoint(40,10634.02);
   3->SetSavedPoint(41,9668.068);
   3->SetSavedPoint(42,8793.909);
   3->SetSavedPoint(43,8002.356);
   3->SetSavedPoint(44,7285.195);
   3->SetSavedPoint(45,6635.078);
   3->SetSavedPoint(46,6045.424);
   3->SetSavedPoint(47,5510.334);
   3->SetSavedPoint(48,5024.515);
   3->SetSavedPoint(49,4583.218);
   3->SetSavedPoint(50,4182.175);
   3->SetSavedPoint(51,3817.547);
   3->SetSavedPoint(52,3485.882);
   3->SetSavedPoint(53,3184.071);
   3->SetSavedPoint(54,2909.314);
   3->SetSavedPoint(55,2659.084);
   3->SetSavedPoint(56,2431.103);
   3->SetSavedPoint(57,2223.313);
   3->SetSavedPoint(58,2033.858);
   3->SetSavedPoint(59,1861.058);
   3->SetSavedPoint(60,1703.394);
   3->SetSavedPoint(61,1559.491);
   3->SetSavedPoint(62,1428.106);
   3->SetSavedPoint(63,1308.111);
   3->SetSavedPoint(64,1198.486);
   3->SetSavedPoint(65,1098.303);
   3->SetSavedPoint(66,1006.723);
   3->SetSavedPoint(67,922.9836);
   3->SetSavedPoint(68,846.3917);
   3->SetSavedPoint(69,776.3187);
   3->SetSavedPoint(70,712.1927);
   3->SetSavedPoint(71,653.4942);
   3->SetSavedPoint(72,599.7504);
   3->SetSavedPoint(73,550.5311);
   3->SetSavedPoint(74,505.4447);
   3->SetSavedPoint(75,464.1347);
   3->SetSavedPoint(76,426.2763);
   3->SetSavedPoint(77,391.5735);
   3->SetSavedPoint(78,359.7564);
   3->SetSavedPoint(79,330.5791);
   3->SetSavedPoint(80,303.817);
   3->SetSavedPoint(81,279.2654);
   3->SetSavedPoint(82,256.7373);
   3->SetSavedPoint(83,236.062);
   3->SetSavedPoint(84,217.0836);
   3->SetSavedPoint(85,199.6598);
   3->SetSavedPoint(86,183.6603);
   3->SetSavedPoint(87,168.9661);
   3->SetSavedPoint(88,155.4686);
   3->SetSavedPoint(89,143.0682);
   3->SetSavedPoint(90,131.6739);
   3->SetSavedPoint(91,121.2024);
   3->SetSavedPoint(92,111.5775);
   3->SetSavedPoint(93,102.7294);
   3->SetSavedPoint(94,94.5942);
   3->SetSavedPoint(95,87.11343);
   3->SetSavedPoint(96,80.23343);
   3->SetSavedPoint(97,73.90508);
   3->SetSavedPoint(98,68.08337);
   3->SetSavedPoint(99,62.72702);
   3->SetSavedPoint(100,57.79818);
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
   4->SetSavedPoint(0,271805.8);
   4->SetSavedPoint(1,246919.4);
   4->SetSavedPoint(2,221957.9);
   4->SetSavedPoint(3,198174.2);
   4->SetSavedPoint(4,176208);
   4->SetSavedPoint(5,156306.8);
   4->SetSavedPoint(6,138489.9);
   4->SetSavedPoint(7,122656.1);
   4->SetSavedPoint(8,108647);
   4->SetSavedPoint(9,96283.95);
   4->SetSavedPoint(10,85387.77);
   4->SetSavedPoint(11,75789.08);
   4->SetSavedPoint(12,67332.8);
   4->SetSavedPoint(13,59879.65);
   4->SetSavedPoint(14,53306.07);
   4->SetSavedPoint(15,47503.27);
   4->SetSavedPoint(16,42375.88);
   4->SetSavedPoint(17,37840.57);
   4->SetSavedPoint(18,33824.64);
   4->SetSavedPoint(19,30264.67);
   4->SetSavedPoint(20,27105.4);
   4->SetSavedPoint(21,24298.62);
   4->SetSavedPoint(22,21802.28);
   4->SetSavedPoint(23,19579.65);
   4->SetSavedPoint(24,17598.62);
   4->SetSavedPoint(25,15831.11);
   4->SetSavedPoint(26,14252.52);
   4->SetSavedPoint(27,12841.26);
   4->SetSavedPoint(28,11578.39);
   4->SetSavedPoint(29,10447.26);
   4->SetSavedPoint(30,9433.224);
   4->SetSavedPoint(31,8523.354);
   4->SetSavedPoint(32,7706.263);
   4->SetSavedPoint(33,6971.889);
   4->SetSavedPoint(34,6311.333);
   4->SetSavedPoint(35,5716.719);
   4->SetSavedPoint(36,5181.065);
   4->SetSavedPoint(37,4698.178);
   4->SetSavedPoint(38,4262.557);
   4->SetSavedPoint(39,3869.309);
   4->SetSavedPoint(40,3514.082);
   4->SetSavedPoint(41,3192.998);
   4->SetSavedPoint(42,2902.596);
   4->SetSavedPoint(43,2639.791);
   4->SetSavedPoint(44,2401.823);
   4->SetSavedPoint(45,2186.227);
   4->SetSavedPoint(46,1990.793);
   4->SetSavedPoint(47,1813.545);
   4->SetSavedPoint(48,1652.71);
   4->SetSavedPoint(49,1506.696);
   4->SetSavedPoint(50,1374.076);
   4->SetSavedPoint(51,1253.565);
   4->SetSavedPoint(52,1144.011);
   4->SetSavedPoint(53,1044.372);
   4->SetSavedPoint(54,953.7158);
   4->SetSavedPoint(55,871.1976);
   4->SetSavedPoint(56,796.058);
   4->SetSavedPoint(57,727.6111);
   4->SetSavedPoint(58,665.2378);
   4->SetSavedPoint(59,608.3789);
   4->SetSavedPoint(60,556.5287);
   4->SetSavedPoint(61,509.2301);
   4->SetSavedPoint(62,466.0694);
   4->SetSavedPoint(63,426.6719);
   4->SetSavedPoint(64,390.6985);
   4->SetSavedPoint(65,357.8417);
   4->SetSavedPoint(66,327.8226);
   4->SetSavedPoint(67,300.3883);
   4->SetSavedPoint(68,275.3093);
   4->SetSavedPoint(69,252.3773);
   4->SetSavedPoint(70,231.4028);
   4->SetSavedPoint(71,212.214);
   4->SetSavedPoint(72,194.6543);
   4->SetSavedPoint(73,178.5816);
   4->SetSavedPoint(74,163.8665);
   4->SetSavedPoint(75,150.3912);
   4->SetSavedPoint(76,138.0484);
   4->SetSavedPoint(77,126.7405);
   4->SetSavedPoint(78,116.3785);
   4->SetSavedPoint(79,106.8814);
   4->SetSavedPoint(80,98.17506);
   4->SetSavedPoint(81,90.19215);
   4->SetSavedPoint(82,82.87112);
   4->SetSavedPoint(83,76.15581);
   4->SetSavedPoint(84,69.99498);
   4->SetSavedPoint(85,64.34182);
   4->SetSavedPoint(86,59.15358);
   4->SetSavedPoint(87,54.3912);
   4->SetSavedPoint(88,50.01898);
   4->SetSavedPoint(89,46.00431);
   4->SetSavedPoint(90,42.31735);
   4->SetSavedPoint(91,38.93081);
   4->SetSavedPoint(92,35.81973);
   4->SetSavedPoint(93,32.96128);
   4->SetSavedPoint(94,30.33456);
   4->SetSavedPoint(95,27.92042);
   4->SetSavedPoint(96,25.70135);
   4->SetSavedPoint(97,23.66131);
   4->SetSavedPoint(98,21.7856);
   4->SetSavedPoint(99,20.06075);
   4->SetSavedPoint(100,18.47441);
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
   5->SetSavedPoint(0,90101.84);
   5->SetSavedPoint(1,81730.83);
   5->SetSavedPoint(2,73341.62);
   5->SetSavedPoint(3,65359.08);
   5->SetSavedPoint(4,57999.82);
   5->SetSavedPoint(5,51346.54);
   5->SetSavedPoint(6,45404.11);
   5->SetSavedPoint(7,40136.15);
   5->SetSavedPoint(8,35487.02);
   5->SetSavedPoint(9,31394.42);
   5->SetSavedPoint(10,27796.22);
   5->SetSavedPoint(11,24633.94);
   5->SetSavedPoint(12,21854.24);
   5->SetSavedPoint(13,19409.45);
   5->SetSavedPoint(14,17257.45);
   5->SetSavedPoint(15,15361.28);
   5->SetSavedPoint(16,13688.69);
   5->SetSavedPoint(17,12211.6);
   5->SetSavedPoint(18,10905.61);
   5->SetSavedPoint(19,9749.481);
   5->SetSavedPoint(20,8724.789);
   5->SetSavedPoint(21,7815.5);
   5->SetSavedPoint(22,7007.666);
   5->SetSavedPoint(23,6289.137);
   5->SetSavedPoint(24,5649.321);
   5->SetSavedPoint(25,5078.969);
   5->SetSavedPoint(26,4569.998);
   5->SetSavedPoint(27,4115.33);
   5->SetSavedPoint(28,3708.766);
   5->SetSavedPoint(29,3344.861);
   5->SetSavedPoint(30,3018.835);
   5->SetSavedPoint(31,2726.478);
   5->SetSavedPoint(32,2464.084);
   5->SetSavedPoint(33,2228.38);
   5->SetSavedPoint(34,2016.479);
   5->SetSavedPoint(35,1825.826);
   5->SetSavedPoint(36,1654.158);
   5->SetSavedPoint(37,1499.47);
   5->SetSavedPoint(38,1359.984);
   5->SetSavedPoint(39,1234.118);
   5->SetSavedPoint(40,1120.466);
   5->SetSavedPoint(41,1017.777);
   5->SetSavedPoint(42,924.9357);
   5->SetSavedPoint(43,840.9468);
   5->SetSavedPoint(44,764.922);
   5->SetSavedPoint(45,696.0673);
   5->SetSavedPoint(46,633.6724);
   5->SetSavedPoint(47,577.1013);
   5->SetSavedPoint(48,525.7844);
   5->SetSavedPoint(49,479.2105);
   5->SetSavedPoint(50,436.9211);
   5->SetSavedPoint(51,398.5041);
   5->SetSavedPoint(52,363.5894);
   5->SetSavedPoint(53,331.8438);
   5->SetSavedPoint(54,302.9674);
   5->SetSavedPoint(55,276.6903);
   5->SetSavedPoint(56,252.7689);
   5->SetSavedPoint(57,230.9837);
   5->SetSavedPoint(58,211.1365);
   5->SetSavedPoint(59,193.0484);
   5->SetSavedPoint(60,176.5576);
   5->SetSavedPoint(61,161.518);
   5->SetSavedPoint(62,147.7973);
   5->SetSavedPoint(63,135.2758);
   5->SetSavedPoint(64,123.8451);
   5->SetSavedPoint(65,113.407);
   5->SetSavedPoint(66,103.8725);
   5->SetSavedPoint(67,95.16086);
   5->SetSavedPoint(68,87.19886);
   5->SetSavedPoint(69,79.91999);
   5->SetSavedPoint(70,73.26387);
   5->SetSavedPoint(71,67.17565);
   5->SetSavedPoint(72,61.60549);
   5->SetSavedPoint(73,56.50803);
   5->SetSavedPoint(74,51.84207);
   5->SetSavedPoint(75,47.57008);
   5->SetSavedPoint(76,43.6579);
   5->SetSavedPoint(77,40.07444);
   5->SetSavedPoint(78,36.79137);
   5->SetSavedPoint(79,33.78288);
   5->SetSavedPoint(80,31.02543);
   5->SetSavedPoint(81,28.49758);
   5->SetSavedPoint(82,26.17975);
   5->SetSavedPoint(83,24.05408);
   5->SetSavedPoint(84,22.10429);
   5->SetSavedPoint(85,20.31549);
   5->SetSavedPoint(86,18.67411);
   5->SetSavedPoint(87,17.16772);
   5->SetSavedPoint(88,15.78499);
   5->SetSavedPoint(89,14.51557);
   5->SetSavedPoint(90,13.34997);
   5->SetSavedPoint(91,12.27953);
   5->SetSavedPoint(92,11.29634);
   5->SetSavedPoint(93,10.39314);
   5->SetSavedPoint(94,9.563303);
   5->SetSavedPoint(95,8.80076);
   5->SetSavedPoint(96,8.099952);
   5->SetSavedPoint(97,7.455793);
   5->SetSavedPoint(98,6.863621);
   5->SetSavedPoint(99,6.319169);
   5->SetSavedPoint(100,5.818525);
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
   6->SetSavedPoint(0,28315.68);
   6->SetSavedPoint(1,25663.35);
   6->SetSavedPoint(2,23002.15);
   6->SetSavedPoint(3,20468.67);
   6->SetSavedPoint(4,18133.35);
   6->SetSavedPoint(5,16023.63);
   6->SetSavedPoint(6,14141.65);
   6->SetSavedPoint(7,12475.97);
   6->SetSavedPoint(8,11008.75);
   6->SetSavedPoint(9,9719.872);
   6->SetSavedPoint(10,8589.204);
   6->SetSavedPoint(11,7597.776);
   6->SetSavedPoint(12,6728.292);
   6->SetSavedPoint(13,5965.303);
   6->SetSavedPoint(14,5295.182);
   6->SetSavedPoint(15,4706.001);
   6->SetSavedPoint(16,4187.374);
   6->SetSavedPoint(17,3730.279);
   6->SetSavedPoint(18,3326.898);
   6->SetSavedPoint(19,2970.453);
   6->SetSavedPoint(20,2655.073);
   6->SetSavedPoint(21,2375.667);
   6->SetSavedPoint(22,2127.82);
   6->SetSavedPoint(23,1907.693);
   6->SetSavedPoint(24,1711.952);
   6->SetSavedPoint(25,1537.69);
   6->SetSavedPoint(26,1382.374);
   6->SetSavedPoint(27,1243.792);
   6->SetSavedPoint(28,1120.01);
   6->SetSavedPoint(29,1009.334);
   6->SetSavedPoint(30,910.2769);
   6->SetSavedPoint(31,821.5352);
   6->SetSavedPoint(32,741.961);
   6->SetSavedPoint(33,670.5435);
   6->SetSavedPoint(34,606.3918);
   6->SetSavedPoint(35,548.7188);
   6->SetSavedPoint(36,496.8288);
   6->SetSavedPoint(37,450.1059);
   6->SetSavedPoint(38,408.0045);
   6->SetSavedPoint(39,370.0401);
   6->SetSavedPoint(40,335.7825);
   6->SetSavedPoint(41,304.8492);
   6->SetSavedPoint(42,276.8996);
   6->SetSavedPoint(43,251.6302);
   6->SetSavedPoint(44,228.7702);
   6->SetSavedPoint(45,208.078);
   6->SetSavedPoint(46,189.3373);
   6->SetSavedPoint(47,172.355);
   6->SetSavedPoint(48,156.958);
   6->SetSavedPoint(49,142.9913);
   6->SetSavedPoint(50,130.3157);
   6->SetSavedPoint(51,118.8065);
   6->SetSavedPoint(52,108.3515);
   6->SetSavedPoint(53,98.84995);
   6->SetSavedPoint(54,90.21115);
   6->SetSavedPoint(55,82.3535);
   6->SetSavedPoint(56,75.20348);
   6->SetSavedPoint(57,68.69479);
   6->SetSavedPoint(58,62.76768);
   6->SetSavedPoint(59,57.36817);
   6->SetSavedPoint(60,52.44754);
   6->SetSavedPoint(61,47.96177);
   6->SetSavedPoint(62,43.87104);
   6->SetSavedPoint(63,40.13934);
   6->SetSavedPoint(64,36.73409);
   6->SetSavedPoint(65,33.62575);
   6->SetSavedPoint(66,30.78759);
   6->SetSavedPoint(67,28.19537);
   6->SetSavedPoint(68,25.8271);
   6->SetSavedPoint(69,23.66284);
   6->SetSavedPoint(70,21.68449);
   6->SetSavedPoint(71,19.87559);
   6->SetSavedPoint(72,18.22121);
   6->SetSavedPoint(73,16.70778);
   6->SetSavedPoint(74,15.32296);
   6->SetSavedPoint(75,14.05552);
   6->SetSavedPoint(76,12.89524);
   6->SetSavedPoint(77,11.83282);
   6->SetSavedPoint(78,10.8598);
   6->SetSavedPoint(79,9.968466);
   6->SetSavedPoint(80,9.151792);
   6->SetSavedPoint(81,8.403371);
   6->SetSavedPoint(82,7.717365);
   6->SetSavedPoint(83,7.088446);
   6->SetSavedPoint(84,6.511755);
   6->SetSavedPoint(85,5.982858);
   6->SetSavedPoint(86,5.497707);
   6->SetSavedPoint(87,5.052606);
   6->SetSavedPoint(88,4.644177);
   6->SetSavedPoint(89,4.269337);
   6->SetSavedPoint(90,3.925267);
   6->SetSavedPoint(91,3.609391);
   6->SetSavedPoint(92,3.319353);
   6->SetSavedPoint(93,3.052998);
   6->SetSavedPoint(94,2.808356);
   6->SetSavedPoint(95,2.583624);
   6->SetSavedPoint(96,2.377152);
   6->SetSavedPoint(97,2.18743);
   6->SetSavedPoint(98,2.013074);
   6->SetSavedPoint(99,1.852819);
   6->SetSavedPoint(100,1.705504);
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
   7->SetSavedPoint(0,8340.889);
   7->SetSavedPoint(1,7556.394);
   7->SetSavedPoint(2,6766.567);
   7->SetSavedPoint(3,6012.699);
   7->SetSavedPoint(4,5316.688);
   7->SetSavedPoint(5,4687.521);
   7->SetSavedPoint(6,4126.419);
   7->SetSavedPoint(7,3630.318);
   7->SetSavedPoint(8,3194.056);
   7->SetSavedPoint(9,2811.659);
   7->SetSavedPoint(10,2477.07);
   7->SetSavedPoint(11,2184.534);
   7->SetSavedPoint(12,1928.776);
   7->SetSavedPoint(13,1705.073);
   7->SetSavedPoint(14,1509.252);
   7->SetSavedPoint(15,1337.662);
   7->SetSavedPoint(16,1187.126);
   7->SetSavedPoint(17,1054.889);
   7->SetSavedPoint(18,938.5689);
   7->SetSavedPoint(19,836.1079);
   7->SetSavedPoint(20,745.7276);
   7->SetSavedPoint(21,665.8919);
   7->SetSavedPoint(22,595.273);
   7->SetSavedPoint(23,532.7218);
   7->SetSavedPoint(24,477.2428);
   7->SetSavedPoint(25,427.9726);
   7->SetSavedPoint(26,384.1613);
   7->SetSavedPoint(27,345.1565);
   7->SetSavedPoint(28,310.3899);
   7->SetSavedPoint(29,279.3656);
   7->SetSavedPoint(30,251.6503);
   7->SetSavedPoint(31,226.8648);
   7->SetSavedPoint(32,204.6767);
   7->SetSavedPoint(33,184.7942);
   7->SetSavedPoint(34,166.9609);
   7->SetSavedPoint(35,150.9509);
   7->SetSavedPoint(36,136.5652);
   7->SetSavedPoint(37,123.628);
   7->SetSavedPoint(38,111.9841);
   7->SetSavedPoint(39,101.4958);
   7->SetSavedPoint(40,92.04141);
   7->SetSavedPoint(41,83.51277);
   7->SetSavedPoint(42,75.81385);
   7->SetSavedPoint(43,68.85921);
   7->SetSavedPoint(44,62.57283);
   7->SetSavedPoint(45,56.88693);
   7->SetSavedPoint(46,51.74103);
   7->SetSavedPoint(47,47.08112);
   7->SetSavedPoint(48,42.85894);
   7->SetSavedPoint(49,39.03128);
   7->SetSavedPoint(50,35.55946);
   7->SetSavedPoint(51,32.40879);
   7->SetSavedPoint(52,29.54816);
   7->SetSavedPoint(53,26.94965);
   7->SetSavedPoint(54,24.58816);
   7->SetSavedPoint(55,22.4411);
   7->SetSavedPoint(56,20.48818);
   7->SetSavedPoint(57,18.7111);
   7->SetSavedPoint(58,17.09338);
   7->SetSavedPoint(59,15.62015);
   7->SetSavedPoint(60,14.278);
   7->SetSavedPoint(61,13.05482);
   7->SetSavedPoint(62,11.93966);
   7->SetSavedPoint(63,10.92265);
   7->SetSavedPoint(64,9.99482);
   7->SetSavedPoint(65,9.148087);
   7->SetSavedPoint(66,8.375117);
   7->SetSavedPoint(67,7.669267);
   7->SetSavedPoint(68,7.024519);
   7->SetSavedPoint(69,6.435411);
   7->SetSavedPoint(70,5.896992);
   7->SetSavedPoint(71,5.404765);
   7->SetSavedPoint(72,4.954648);
   7->SetSavedPoint(73,4.542932);
   7->SetSavedPoint(74,4.166246);
   7->SetSavedPoint(75,3.821525);
   7->SetSavedPoint(76,3.505981);
   7->SetSavedPoint(77,3.217078);
   7->SetSavedPoint(78,2.952506);
   7->SetSavedPoint(79,2.710162);
   7->SetSavedPoint(80,2.488132);
   7->SetSavedPoint(81,2.28467);
   7->SetSavedPoint(82,2.098185);
   7->SetSavedPoint(83,1.927226);
   7->SetSavedPoint(84,1.77047);
   7->SetSavedPoint(85,1.62671);
   7->SetSavedPoint(86,1.494843);
   7->SetSavedPoint(87,1.373865);
   7->SetSavedPoint(88,1.262856);
   7->SetSavedPoint(89,1.160976);
   7->SetSavedPoint(90,1.06746);
   7->SetSavedPoint(91,0.9816067);
   7->SetSavedPoint(92,0.9027752);
   7->SetSavedPoint(93,0.83038);
   7->SetSavedPoint(94,0.7638852);
   7->SetSavedPoint(95,0.7028006);
   7->SetSavedPoint(96,0.6466779);
   7->SetSavedPoint(97,0.5951064);
   7->SetSavedPoint(98,0.5477104);
   7->SetSavedPoint(99,0.5041458);
   7->SetSavedPoint(100,0.4640974);
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
   8->SetSavedPoint(0,2034.997);
   8->SetSavedPoint(1,1852.409);
   8->SetSavedPoint(2,1666.471);
   8->SetSavedPoint(3,1487.053);
   8->SetSavedPoint(4,1319.744);
   8->SetSavedPoint(5,1167.158);
   8->SetSavedPoint(6,1030.032);
   8->SetSavedPoint(7,907.9957);
   8->SetSavedPoint(8,800.091);
   8->SetSavedPoint(9,705.0828);
   8->SetSavedPoint(10,621.6504);
   8->SetSavedPoint(11,548.4947);
   8->SetSavedPoint(12,484.3958);
   8->SetSavedPoint(13,428.2398);
   8->SetSavedPoint(14,379.0276);
   8->SetSavedPoint(15,335.8743);
   8->SetSavedPoint(16,298.0019);
   8->SetSavedPoint(17,264.7306);
   8->SetSavedPoint(18,235.4683);
   8->SetSavedPoint(19,209.7007);
   8->SetSavedPoint(20,186.9816);
   8->SetSavedPoint(21,166.9242);
   8->SetSavedPoint(22,149.1932);
   8->SetSavedPoint(23,133.4981);
   8->SetSavedPoint(24,119.5867);
   8->SetSavedPoint(25,107.2401);
   8->SetSavedPoint(26,96.26842);
   8->SetSavedPoint(27,86.50612);
   8->SetSavedPoint(28,77.80921);
   8->SetSavedPoint(29,70.05213);
   8->SetSavedPoint(30,63.12523);
   8->SetSavedPoint(31,56.93265);
   8->SetSavedPoint(32,51.39045);
   8->SetSavedPoint(33,46.42506);
   8->SetSavedPoint(34,41.97187);
   8->SetSavedPoint(35,37.97406);
   8->SetSavedPoint(36,34.38163);
   8->SetSavedPoint(37,31.15048);
   8->SetSavedPoint(38,28.24169);
   8->SetSavedPoint(39,25.62083);
   8->SetSavedPoint(40,23.25745);
   8->SetSavedPoint(41,21.12454);
   8->SetSavedPoint(42,19.19815);
   8->SetSavedPoint(43,17.45698);
   8->SetSavedPoint(44,15.88211);
   8->SetSavedPoint(45,14.45665);
   8->SetSavedPoint(46,13.16559);
   8->SetSavedPoint(47,11.9955);
   8->SetSavedPoint(48,10.93439);
   8->SetSavedPoint(49,9.971536);
   8->SetSavedPoint(50,9.097335);
   8->SetSavedPoint(51,8.303185);
   8->SetSavedPoint(52,7.581371);
   8->SetSavedPoint(53,6.924963);
   8->SetSavedPoint(54,6.327737);
   8->SetSavedPoint(55,5.784095);
   8->SetSavedPoint(56,5.288999);
   8->SetSavedPoint(57,4.83791);
   8->SetSavedPoint(58,4.426737);
   8->SetSavedPoint(59,4.051791);
   8->SetSavedPoint(60,3.709739);
   8->SetSavedPoint(61,3.397574);
   8->SetSavedPoint(62,3.112574);
   8->SetSavedPoint(63,2.852279);
   8->SetSavedPoint(64,2.614462);
   8->SetSavedPoint(65,2.397106);
   8->SetSavedPoint(66,2.198385);
   8->SetSavedPoint(67,2.01664);
   8->SetSavedPoint(68,1.850369);
   8->SetSavedPoint(69,1.698207);
   8->SetSavedPoint(70,1.558915);
   8->SetSavedPoint(71,1.431368);
   8->SetSavedPoint(72,1.314542);
   8->SetSavedPoint(73,1.207507);
   8->SetSavedPoint(74,1.109415);
   8->SetSavedPoint(75,1.019497);
   8->SetSavedPoint(76,0.9370504);
   8->SetSavedPoint(77,0.8614354);
   8->SetSavedPoint(78,0.7920696);
   8->SetSavedPoint(79,0.7284217);
   8->SetSavedPoint(80,0.670007);
   8->SetSavedPoint(81,0.6163833);
   8->SetSavedPoint(82,0.5671472);
   8->SetSavedPoint(83,0.52193);
   8->SetSavedPoint(84,0.4803953);
   8->SetSavedPoint(85,0.4422354);
   8->SetSavedPoint(86,0.4071694);
   8->SetSavedPoint(87,0.3749401);
   8->SetSavedPoint(88,0.3453127);
   8->SetSavedPoint(89,0.3180722);
   8->SetSavedPoint(90,0.2930217);
   8->SetSavedPoint(91,0.2699813);
   8->SetSavedPoint(92,0.248786);
   8->SetSavedPoint(93,0.2292849);
   8->SetSavedPoint(94,0.2113397);
   8->SetSavedPoint(95,0.1948235);
   8->SetSavedPoint(96,0.1796203);
   8->SetSavedPoint(97,0.1656236);
   8->SetSavedPoint(98,0.1527356);
   8->SetSavedPoint(99,0.1408669);
   8->SetSavedPoint(100,0.1299353);
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
   9->SetSavedPoint(0,437.4747);
   9->SetSavedPoint(1,401.1032);
   9->SetSavedPoint(2,363.4825);
   9->SetSavedPoint(3,326.6145);
   9->SetSavedPoint(4,291.7241);
   9->SetSavedPoint(5,259.4667);
   9->SetSavedPoint(6,230.1153);
   9->SetSavedPoint(7,203.7022);
   9->SetSavedPoint(8,180.1172);
   9->SetSavedPoint(9,159.1721);
   9->SetSavedPoint(10,140.6421);
   9->SetSavedPoint(11,124.2915);
   9->SetSavedPoint(12,109.8889);
   9->SetSavedPoint(13,97.2155);
   9->SetSavedPoint(14,86.06983);
   9->SetSavedPoint(15,76.26917);
   9->SetSavedPoint(16,67.64984);
   9->SetSavedPoint(17,60.06643);
   9->SetSavedPoint(18,53.39051);
   9->SetSavedPoint(19,47.50913);
   9->SetSavedPoint(20,42.3233);
   9->SetSavedPoint(21,37.7464);
   9->SetSavedPoint(22,33.70281);
   9->SetSavedPoint(23,30.12655);
   9->SetSavedPoint(24,26.96007);
   9->SetSavedPoint(25,24.1532);
   9->SetSavedPoint(26,21.66222);
   9->SetSavedPoint(27,19.44896);
   9->SetSavedPoint(28,17.48016);
   9->SetSavedPoint(29,15.72675);
   9->SetSavedPoint(30,14.16335);
   9->SetSavedPoint(31,12.76775);
   9->SetSavedPoint(32,11.52053);
   9->SetSavedPoint(33,10.40465);
   9->SetSavedPoint(34,9.405187);
   9->SetSavedPoint(35,8.509029);
   9->SetSavedPoint(36,7.704651);
   9->SetSavedPoint(37,6.981911);
   9->SetSavedPoint(38,6.331871);
   9->SetSavedPoint(39,5.746649);
   9->SetSavedPoint(40,5.219281);
   9->SetSavedPoint(41,4.743612);
   9->SetSavedPoint(42,4.314191);
   9->SetSavedPoint(43,3.926185);
   9->SetSavedPoint(44,3.575306);
   9->SetSavedPoint(45,3.257745);
   9->SetSavedPoint(46,2.970114);
   9->SetSavedPoint(47,2.709393);
   9->SetSavedPoint(48,2.472891);
   9->SetSavedPoint(49,2.258208);
   9->SetSavedPoint(50,2.063197);
   9->SetSavedPoint(51,1.885939);
   9->SetSavedPoint(52,1.724715);
   9->SetSavedPoint(53,1.577984);
   9->SetSavedPoint(54,1.444364);
   9->SetSavedPoint(55,1.322614);
   9->SetSavedPoint(56,1.211618);
   9->SetSavedPoint(57,1.110371);
   9->SetSavedPoint(58,1.017971);
   9->SetSavedPoint(59,0.9336008);
   9->SetSavedPoint(60,0.8565268);
   9->SetSavedPoint(61,0.7860848);
   9->SetSavedPoint(62,0.7216753);
   9->SetSavedPoint(63,0.6627559);
   9->SetSavedPoint(64,0.608836);
   9->SetSavedPoint(65,0.5594714);
   9->SetSavedPoint(66,0.5142593);
   9->SetSavedPoint(67,0.4728346);
   9->SetSavedPoint(68,0.4348662);
   9->SetSavedPoint(69,0.4000532);
   9->SetSavedPoint(70,0.3681222);
   9->SetSavedPoint(71,0.3388249);
   9->SetSavedPoint(72,0.3119353);
   9->SetSavedPoint(73,0.2872478);
   9->SetSavedPoint(74,0.2645751);
   9->SetSavedPoint(75,0.2437465);
   9->SetSavedPoint(76,0.2246066);
   9->SetSavedPoint(77,0.2070134);
   9->SetSavedPoint(78,0.1908378);
   9->SetSavedPoint(79,0.1759614);
   9->SetSavedPoint(80,0.1622764);
   9->SetSavedPoint(81,0.1496843);
   9->SetSavedPoint(82,0.1380949);
   9->SetSavedPoint(83,0.1274259);
   9->SetSavedPoint(84,0.117602);
   9->SetSavedPoint(85,0.1085542);
   9->SetSavedPoint(86,0.1002193);
   9->SetSavedPoint(87,0.09253957);
   9->SetSavedPoint(88,0.08546202);
   9->SetSavedPoint(89,0.07893813);
   9->SetSavedPoint(90,0.07292339);
   9->SetSavedPoint(91,0.06737702);
   9->SetSavedPoint(92,0.06226157);
   9->SetSavedPoint(93,0.05754272);
   9->SetSavedPoint(94,0.05318893);
   9->SetSavedPoint(95,0.04917127);
   9->SetSavedPoint(96,0.04546315);
   9->SetSavedPoint(97,0.04204017);
   9->SetSavedPoint(98,0.03887987);
   9->SetSavedPoint(99,0.03596165);
   9->SetSavedPoint(100,0.03326653);
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
   10->SetSavedPoint(0,79.51359);
   10->SetSavedPoint(1,73.42546);
   10->SetSavedPoint(2,67.03358);
   10->SetSavedPoint(3,60.67385);
   10->SetSavedPoint(4,54.56544);
   10->SetSavedPoint(5,48.83782);
   10->SetSavedPoint(6,43.55709);
   10->SetSavedPoint(7,38.747);
   10->SetSavedPoint(8,34.40418);
   10->SetSavedPoint(9,30.50879);
   10->SetSavedPoint(10,27.03176);
   10->SetSavedPoint(11,23.93945);
   10->SetSavedPoint(12,21.19677);
   10->SetSavedPoint(13,18.76906);
   10->SetSavedPoint(14,16.62326);
   10->SetSavedPoint(15,14.72854);
   10->SetSavedPoint(16,13.05661);
   10->SetSavedPoint(17,11.58179);
   10->SetSavedPoint(18,10.28101);
   10->SetSavedPoint(19,9.133631);
   10->SetSavedPoint(20,8.121309);
   10->SetSavedPoint(21,7.227801);
   10->SetSavedPoint(22,6.438758);
   10->SetSavedPoint(23,5.741541);
   10->SetSavedPoint(24,5.125032);
   10->SetSavedPoint(25,4.579468);
   10->SetSavedPoint(26,4.09628);
   10->SetSavedPoint(27,3.667956);
   10->SetSavedPoint(28,3.287911);
   10->SetSavedPoint(29,2.950376);
   10->SetSavedPoint(30,2.650294);
   10->SetSavedPoint(31,2.383236);
   10->SetSavedPoint(32,2.145318);
   10->SetSavedPoint(33,1.933137);
   10->SetSavedPoint(34,1.743705);
   10->SetSavedPoint(35,1.574401);
   10->SetSavedPoint(36,1.422924);
   10->SetSavedPoint(37,1.287251);
   10->SetSavedPoint(38,1.165603);
   10->SetSavedPoint(39,1.056415);
   10->SetSavedPoint(40,0.9583068);
   10->SetSavedPoint(41,0.870063);
   10->SetSavedPoint(42,0.7906104);
   10->SetSavedPoint(43,0.7190011);
   10->SetSavedPoint(44,0.6543969);
   10->SetSavedPoint(45,0.5960561);
   10->SetSavedPoint(46,0.5433214);
   10->SetSavedPoint(47,0.4956098);
   10->SetSavedPoint(48,0.4524037);
   10->SetSavedPoint(49,0.4132431);
   10->SetSavedPoint(50,0.3777186);
   10->SetSavedPoint(51,0.3454657);
   10->SetSavedPoint(52,0.3161591);
   10->SetSavedPoint(53,0.2895088);
   10->SetSavedPoint(54,0.2652554);
   10->SetSavedPoint(55,0.2431668);
   10->SetSavedPoint(56,0.2230353);
   10->SetSavedPoint(57,0.2046748);
   10->SetSavedPoint(58,0.1879182);
   10->SetSavedPoint(59,0.1726152);
   10->SetSavedPoint(60,0.158631);
   10->SetSavedPoint(61,0.1458442);
   10->SetSavedPoint(62,0.1341452);
   10->SetSavedPoint(63,0.1234354);
   10->SetSavedPoint(64,0.1136258);
   10->SetSavedPoint(65,0.1046359);
   10->SetSavedPoint(66,0.09639303);
   10->SetSavedPoint(67,0.08883126);
   10->SetSavedPoint(68,0.08189102);
   10->SetSavedPoint(69,0.07551825);
   10->SetSavedPoint(70,0.06966393);
   10->SetSavedPoint(71,0.06428355);
   10->SetSavedPoint(72,0.05933666);
   10->SetSavedPoint(73,0.05478651);
   10->SetSavedPoint(74,0.05059962);
   10->SetSavedPoint(75,0.04674554);
   10->SetSavedPoint(76,0.04319652);
   10->SetSavedPoint(77,0.03992725);
   10->SetSavedPoint(78,0.03691464);
   10->SetSavedPoint(79,0.03413762);
   10->SetSavedPoint(80,0.03157695);
   10->SetSavedPoint(81,0.02921503);
   10->SetSavedPoint(82,0.02703578);
   10->SetSavedPoint(83,0.02502449);
   10->SetSavedPoint(84,0.02316768);
   10->SetSavedPoint(85,0.02145302);
   10->SetSavedPoint(86,0.01986919);
   10->SetSavedPoint(87,0.01840585);
   10->SetSavedPoint(88,0.01705347);
   10->SetSavedPoint(89,0.01580335);
   10->SetSavedPoint(90,0.01464748);
   10->SetSavedPoint(91,0.0135785);
   10->SetSavedPoint(92,0.01258967);
   10->SetSavedPoint(93,0.01167476);
   10->SetSavedPoint(94,0.01082808);
   10->SetSavedPoint(95,0.01004438);
   10->SetSavedPoint(96,0.009318827);
   10->SetSavedPoint(97,0.008646972);
   10->SetSavedPoint(98,0.008024724);
   10->SetSavedPoint(99,0.007448314);
   10->SetSavedPoint(100,0.006914268);
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
