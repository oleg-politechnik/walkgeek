<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="walkgeek-eagle">
<packages>
<package name="QFN40-6X6">
<description>&lt;b&gt;RHA (S-PQFP-N40) 6 x 6 mm&lt;/b&gt;&lt;p&gt;
Source: http://focus.ti.com/lit/ds/symlink/tps65020.pdf</description>
<wire x1="-3.025" y1="3.025" x2="3.025" y2="3.025" width="0.1016" layer="51"/>
<wire x1="3.025" y1="3.025" x2="3.025" y2="-3.025" width="0.1016" layer="51"/>
<wire x1="3.025" y1="-3.025" x2="-3.025" y2="-3.025" width="0.1016" layer="51"/>
<wire x1="-3.025" y1="-3.025" x2="-3.025" y2="3.025" width="0.1016" layer="51"/>
<circle x="-2.7" y="2.25" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="2.25" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="1.75" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="1.75" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="1.25" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="1.25" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="0.75" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="0.75" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="0.25" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="0.25" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="-0.25" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="-0.25" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="-0.75" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="-0.75" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="-1.25" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="-1.25" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="-1.75" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="-1.75" radius="0.125" width="0" layer="31"/>
<circle x="-2.7" y="-2.25" radius="0.2" width="0" layer="29"/>
<circle x="-2.7" y="-2.25" radius="0.125" width="0" layer="31"/>
<circle x="-2.25" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="-2.25" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="-1.75" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="-1.75" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="-1.25" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="-1.25" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="-0.75" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="-0.75" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="-0.25" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="-0.25" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="0.25" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="0.25" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="0.75" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="0.75" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="1.25" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="1.25" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="1.75" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="1.75" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="2.25" y="-2.7" radius="0.2" width="0" layer="29"/>
<circle x="2.25" y="-2.7" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="-2.25" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="-2.25" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="-1.75" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="-1.75" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="-1.25" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="-1.25" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="-0.75" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="-0.75" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="-0.25" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="-0.25" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="0.25" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="0.25" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="0.75" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="0.75" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="1.25" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="1.25" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="1.75" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="1.75" radius="0.125" width="0" layer="31"/>
<circle x="2.7" y="2.25" radius="0.2" width="0" layer="29"/>
<circle x="2.7" y="2.25" radius="0.125" width="0" layer="31"/>
<circle x="2.25" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="2.25" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="1.75" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="1.75" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="1.25" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="1.25" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="0.75" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="0.75" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="0.25" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="0.25" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="-0.25" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="-0.25" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="-0.75" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="-0.75" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="-1.25" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="-1.25" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="-1.75" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="-1.75" y="2.7" radius="0.125" width="0" layer="31"/>
<circle x="-2.25" y="2.7" radius="0.2" width="0" layer="29"/>
<circle x="-2.25" y="2.7" radius="0.125" width="0" layer="31"/>
<smd name="1" x="-3.025" y="2.25" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="2" x="-3.025" y="1.75" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="3" x="-3.025" y="1.25" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="4" x="-3.025" y="0.75" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="5" x="-3.025" y="0.25" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="6" x="-3.025" y="-0.25" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="7" x="-3.025" y="-0.75" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="8" x="-3.025" y="-1.25" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="9" x="-3.025" y="-1.75" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="10" x="-3.025" y="-2.25" dx="0.95" dy="0.28" layer="1" roundness="100" stop="no" cream="no"/>
<smd name="11" x="-2.25" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="12" x="-1.75" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="13" x="-1.25" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="14" x="-0.75" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="15" x="-0.25" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="16" x="0.25" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="17" x="0.75" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="18" x="1.25" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="19" x="1.75" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="20" x="2.25" y="-3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R90" stop="no" cream="no"/>
<smd name="21" x="3.025" y="-2.25" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="22" x="3.025" y="-1.75" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="23" x="3.025" y="-1.25" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="24" x="3.025" y="-0.75" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="25" x="3.025" y="-0.25" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="26" x="3.025" y="0.25" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="27" x="3.025" y="0.75" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="28" x="3.025" y="1.25" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="29" x="3.025" y="1.75" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="30" x="3.025" y="2.25" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R180" stop="no" cream="no"/>
<smd name="31" x="2.25" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="32" x="1.75" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="33" x="1.25" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="34" x="0.75" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="35" x="0.25" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="36" x="-0.25" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="37" x="-0.75" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="38" x="-1.25" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="39" x="-1.75" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<smd name="40" x="-2.25" y="3.025" dx="0.95" dy="0.28" layer="1" roundness="100" rot="R270" stop="no" cream="no"/>
<text x="-2.9" y="3.99" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.9" y="-5.44" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.4" y1="2.05" x2="-2.7" y2="2.45" layer="29"/>
<rectangle x1="-3.375" y1="2.125" x2="-2.7" y2="2.375" layer="31"/>
<rectangle x1="-3.4" y1="1.55" x2="-2.7" y2="1.95" layer="29"/>
<rectangle x1="-3.375" y1="1.625" x2="-2.7" y2="1.875" layer="31"/>
<rectangle x1="-3.4" y1="1.05" x2="-2.7" y2="1.45" layer="29"/>
<rectangle x1="-3.375" y1="1.125" x2="-2.7" y2="1.375" layer="31"/>
<rectangle x1="-3.4" y1="0.55" x2="-2.7" y2="0.95" layer="29"/>
<rectangle x1="-3.375" y1="0.625" x2="-2.7" y2="0.875" layer="31"/>
<rectangle x1="-3.4" y1="0.05" x2="-2.7" y2="0.45" layer="29"/>
<rectangle x1="-3.375" y1="0.125" x2="-2.7" y2="0.375" layer="31"/>
<rectangle x1="-3.4" y1="-0.45" x2="-2.7" y2="-0.05" layer="29"/>
<rectangle x1="-3.375" y1="-0.375" x2="-2.7" y2="-0.125" layer="31"/>
<rectangle x1="-3.4" y1="-0.95" x2="-2.7" y2="-0.55" layer="29"/>
<rectangle x1="-3.375" y1="-0.875" x2="-2.7" y2="-0.625" layer="31"/>
<rectangle x1="-3.4" y1="-1.45" x2="-2.7" y2="-1.05" layer="29"/>
<rectangle x1="-3.375" y1="-1.375" x2="-2.7" y2="-1.125" layer="31"/>
<rectangle x1="-3.4" y1="-1.95" x2="-2.7" y2="-1.55" layer="29"/>
<rectangle x1="-3.375" y1="-1.875" x2="-2.7" y2="-1.625" layer="31"/>
<rectangle x1="-3.4" y1="-2.45" x2="-2.7" y2="-2.05" layer="29"/>
<rectangle x1="-3.375" y1="-2.375" x2="-2.7" y2="-2.125" layer="31"/>
<rectangle x1="-2.6" y1="-3.25" x2="-1.9" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="-2.5875" y1="-3.1625" x2="-1.9125" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="-2.1" y1="-3.25" x2="-1.4" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="-2.0875" y1="-3.1625" x2="-1.4125" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="-1.6" y1="-3.25" x2="-0.9" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="-1.5875" y1="-3.1625" x2="-0.9125" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="-1.1" y1="-3.25" x2="-0.4" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="-1.0875" y1="-3.1625" x2="-0.4125" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="-0.6" y1="-3.25" x2="0.1" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="-0.5875" y1="-3.1625" x2="0.0875" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="-0.1" y1="-3.25" x2="0.6" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="-0.0875" y1="-3.1625" x2="0.5875" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="0.4" y1="-3.25" x2="1.1" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="0.4125" y1="-3.1625" x2="1.0875" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="0.9" y1="-3.25" x2="1.6" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="0.9125" y1="-3.1625" x2="1.5875" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="1.4" y1="-3.25" x2="2.1" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="1.4125" y1="-3.1625" x2="2.0875" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="1.9" y1="-3.25" x2="2.6" y2="-2.85" layer="29" rot="R90"/>
<rectangle x1="1.9125" y1="-3.1625" x2="2.5875" y2="-2.9125" layer="31" rot="R90"/>
<rectangle x1="2.7" y1="-2.45" x2="3.4" y2="-2.05" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="-2.375" x2="3.375" y2="-2.125" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="-1.95" x2="3.4" y2="-1.55" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="-1.875" x2="3.375" y2="-1.625" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="-1.45" x2="3.4" y2="-1.05" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="-1.375" x2="3.375" y2="-1.125" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="-0.95" x2="3.4" y2="-0.55" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="-0.875" x2="3.375" y2="-0.625" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="-0.45" x2="3.4" y2="-0.05" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="-0.375" x2="3.375" y2="-0.125" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="0.05" x2="3.4" y2="0.45" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="0.125" x2="3.375" y2="0.375" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="0.55" x2="3.4" y2="0.95" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="0.625" x2="3.375" y2="0.875" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="1.05" x2="3.4" y2="1.45" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="1.125" x2="3.375" y2="1.375" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="1.55" x2="3.4" y2="1.95" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="1.625" x2="3.375" y2="1.875" layer="31" rot="R180"/>
<rectangle x1="2.7" y1="2.05" x2="3.4" y2="2.45" layer="29" rot="R180"/>
<rectangle x1="2.7" y1="2.125" x2="3.375" y2="2.375" layer="31" rot="R180"/>
<rectangle x1="1.9" y1="2.85" x2="2.6" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="1.9125" y1="2.9125" x2="2.5875" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="1.4" y1="2.85" x2="2.1" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="1.4125" y1="2.9125" x2="2.0875" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="0.9" y1="2.85" x2="1.6" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="0.9125" y1="2.9125" x2="1.5875" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="0.4" y1="2.85" x2="1.1" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="0.4125" y1="2.9125" x2="1.0875" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-0.1" y1="2.85" x2="0.6" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="-0.0875" y1="2.9125" x2="0.5875" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-0.6" y1="2.85" x2="0.1" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="-0.5875" y1="2.9125" x2="0.0875" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-1.1" y1="2.85" x2="-0.4" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="-1.0875" y1="2.9125" x2="-0.4125" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-1.6" y1="2.85" x2="-0.9" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="-1.5875" y1="2.9125" x2="-0.9125" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-2.1" y1="2.85" x2="-1.4" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="-2.0875" y1="2.9125" x2="-1.4125" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-2.6" y1="2.85" x2="-1.9" y2="3.25" layer="29" rot="R270"/>
<rectangle x1="-2.5875" y1="2.9125" x2="-1.9125" y2="3.1625" layer="31" rot="R270"/>
<rectangle x1="-3" y1="2.75" x2="-2.75" y2="3" layer="1"/>
<pad name="EXP@3" x="0" y="1.3" drill="0.4"/>
<pad name="EXP@4" x="-1.3" y="0" drill="0.4"/>
<pad name="EXP@5" x="1.3" y="0" drill="0.4"/>
<pad name="EXP@9" x="0" y="-1.3" drill="0.4"/>
</package>
<package name="NOKIA1100_KEY_PAD">
<circle x="0" y="0" radius="2.05" width="1.4" layer="1"/>
<smd name="OUTER" x="0" y="2" dx="1.2" dy="1.2" layer="1" roundness="100" rot="R90" stop="no" thermals="no" cream="no"/>
<circle x="0" y="0" radius="0.45" width="0.9" layer="1"/>
<pad name="INNER" x="-0.4" y="0" drill="0.5" diameter="0.9" stop="no" thermals="no"/>
<pad name="INNER2" x="0.4" y="0" drill="0.5" diameter="0.9" stop="no" thermals="no"/>
<smd name="OUTER1" x="0" y="-2" dx="1.2" dy="1.2" layer="1" roundness="100" rot="R90" stop="no" thermals="no" cream="no"/>
<circle x="0" y="0" radius="1.4" width="2.8" layer="29"/>
</package>
<package name="NOKIA1100_DISP">
<smd name="1" x="4.69" y="0" dx="1.5" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="2" x="3.22" y="0" dx="0.84" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="3" x="2.08" y="0" dx="0.84" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="4" x="0.94" y="0" dx="0.84" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="5" x="-0.22" y="0" dx="0.84" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="6" x="-1.36" y="0" dx="0.84" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="7" x="-2.5" y="0" dx="0.84" dy="3.3" layer="1" thermals="no" cream="no"/>
<smd name="8" x="-3.97" y="0" dx="1.5" dy="3.3" layer="1" thermals="no" cream="no"/>
<wire x1="-18.25" y1="-9.8" x2="-18.25" y2="-13.3" width="0.127" layer="51"/>
<wire x1="18.25" y1="-9.8" x2="18.25" y2="-13.3" width="0.127" layer="51"/>
<wire x1="-18.25" y1="-26.3" x2="-18.25" y2="-29.8" width="0.127" layer="51"/>
<wire x1="18.25" y1="-26.3" x2="18.25" y2="-29.8" width="0.127" layer="51"/>
<hole x="-17" y="4.5" drill="2.1"/>
</package>
<package name="NOKIA1100_EXT_CONN">
<smd name="BTN" x="-4.7" y="4.7" dx="3" dy="2" layer="1" rot="R90" thermals="no" cream="no"/>
<smd name="A" x="3.4" y="10.05" dx="2" dy="2.7" layer="1" thermals="no" cream="no"/>
<smd name="AGND" x="2" y="6.9" dx="2" dy="2.4" layer="1" thermals="no" cream="no"/>
<smd name="B" x="0.7" y="10.05" dx="2" dy="2.7" layer="1" thermals="no" cream="no"/>
<hole x="-2" y="4" drill="2"/>
</package>
<package name="NOKIA1100_VIBRATOR">
<smd name="1" x="0" y="-1.15" dx="8.7" dy="1.7" layer="1" thermals="no" cream="no"/>
<smd name="2" x="0" y="1.15" dx="8.7" dy="1.7" layer="1" thermals="no" cream="no"/>
</package>
<package name="NOKIA1100_BATTERY_CONN">
<smd name="-" x="0" y="0" dx="3.5" dy="1.5" layer="1" rot="R90"/>
<smd name="SERV" x="3" y="0" dx="3.5" dy="1.5" layer="1" rot="R90"/>
<smd name="+" x="6" y="0" dx="3.5" dy="1.5" layer="1" rot="R90"/>
<smd name="P$1" x="1.55" y="3.5" dx="2" dy="0.8" layer="1" rot="R90"/>
<smd name="P$2" x="1.1" y="5.5" dx="2" dy="1.7" layer="1" rot="R90"/>
<smd name="P$3" x="4.55" y="3.5" dx="2" dy="0.8" layer="1" rot="R90"/>
<smd name="P$4" x="4.1" y="5.5" dx="2" dy="1.7" layer="1" rot="R90"/>
</package>
<package name="MICRO3">
<description>&lt;b&gt;Micro3 TM Package Outline&lt;/b&gt;&lt;p&gt;
www.irf.com / irlml5203.pdf</description>
<wire x1="-0.6" y1="0.65" x2="0.6" y2="0.65" width="0.1016" layer="51"/>
<wire x1="1.45" y1="-0.65" x2="0.35" y2="-0.65" width="0.1016" layer="51"/>
<wire x1="-0.35" y1="-0.65" x2="-1.45" y2="-0.65" width="0.1016" layer="51"/>
<smd name="1" x="-0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="2" x="0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="3" x="0" y="1" dx="0.8" dy="0.9" layer="1"/>
<text x="-1.6" y="1.6" size="1.778" layer="25">&gt;NAME</text>
<text x="-1.5" y="-3.4" size="1.778" layer="27">&gt;VALUE</text>
<rectangle x1="-0.27" y1="0.66" x2="0.27" y2="1.25" layer="51"/>
<rectangle x1="-1.22" y1="-1.25" x2="-0.68" y2="-0.65" layer="51"/>
<rectangle x1="0.68" y1="-1.25" x2="1.22" y2="-0.64" layer="51"/>
</package>
<package name="SOT23-6L">
<description>&lt;b&gt;Small Outline Transistor&lt;/b&gt;</description>
<wire x1="1.422" y1="-0.81" x2="-1.422" y2="-0.81" width="0.1524" layer="51"/>
<wire x1="-1.422" y1="0.81" x2="1.422" y2="0.81" width="0.1524" layer="51"/>
<smd name="1" x="-0.95" y="-1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="2" x="0" y="-1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="3" x="0.95" y="-1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="4" x="0.95" y="1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="5" x="0" y="1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="6" x="-0.95" y="1.3" dx="0.55" dy="1.2" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.2" y1="-1.5" x2="-0.7" y2="-0.85" layer="51"/>
<rectangle x1="-0.25" y1="-1.5" x2="0.25" y2="-0.85" layer="51"/>
<rectangle x1="0.7" y1="-1.5" x2="1.2" y2="-0.85" layer="51"/>
<rectangle x1="0.7" y1="0.85" x2="1.2" y2="1.5" layer="51"/>
<rectangle x1="-0.25" y1="0.85" x2="0.25" y2="1.5" layer="51"/>
<rectangle x1="-1.2" y1="0.85" x2="-0.7" y2="1.5" layer="51"/>
</package>
<package name="TFC-WPCE-08">
<smd name="SH1" x="0.45" y="-13.55" dx="1.4" dy="1.9" layer="1"/>
<smd name="SH2" x="13.6" y="-14.55" dx="1.4" dy="1.9" layer="1"/>
<smd name="SNS1" x="2.05" y="-0.3" dx="1.8" dy="1.2" layer="1"/>
<smd name="SH3" x="4.9" y="-0.3" dx="1.8" dy="1.2" layer="1"/>
<smd name="SNS2" x="7.75" y="-0.3" dx="1.8" dy="1.2" layer="1"/>
<smd name="SH4" x="10.6" y="-0.3" dx="1.8" dy="1.2" layer="1"/>
<smd name="DAT1" x="1.22" y="-10.7" dx="0.7" dy="1.5" layer="1"/>
<smd name="DAT0" x="2.32" y="-10.7" dx="0.7" dy="1.5" layer="1"/>
<smd name="VSS" x="3.42" y="-10.9" dx="0.7" dy="1.5" layer="1"/>
<smd name="CLK" x="4.52" y="-10.7" dx="0.7" dy="1.5" layer="1"/>
<smd name="VDD" x="5.62" y="-10.9" dx="0.7" dy="1.5" layer="1"/>
<smd name="CMD" x="6.72" y="-10.7" dx="0.7" dy="1.5" layer="1"/>
<smd name="CD/DAT3" x="7.82" y="-10.3" dx="0.7" dy="1.5" layer="1"/>
<smd name="DAT2" x="8.92" y="-10.7" dx="0.7" dy="1.5" layer="1"/>
<wire x1="0" y1="0" x2="0" y2="-12.3" width="0.3" layer="51"/>
<wire x1="0.8" y1="0" x2="0" y2="0" width="0.3" layer="51"/>
<wire x1="11.9" y1="0" x2="14" y2="0" width="0.3" layer="51"/>
<wire x1="0" y1="-14.8" x2="0" y2="-15.2" width="0.3" layer="51"/>
<wire x1="0" y1="-15.2" x2="12.6" y2="-15.2" width="0.3" layer="51"/>
<wire x1="14" y1="0" x2="14" y2="-13.3" width="0.3" layer="51"/>
<text x="3" y="-3" size="1.27" layer="25" font="vector" align="top-left">&gt;NAME</text>
<text x="3" y="-6" size="1.27" layer="27" font="vector" align="top-left">&gt;VALUE</text>
<wire x1="0" y1="-15.2" x2="0" y2="-28.2" width="0.3" layer="27" style="shortdash"/>
<wire x1="14" y1="-15.8" x2="14" y2="-28.2" width="0.3" layer="27" style="shortdash"/>
<wire x1="14" y1="-28.2" x2="0" y2="-28.2" width="0.3" layer="27" style="shortdash"/>
</package>
<package name="R0402">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<smd name="1" x="-0.45" y="0" dx="0.6" dy="0.8" layer="1"/>
<smd name="2" x="0.45" y="0" dx="0.6" dy="0.8" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
</package>
<package name="R0603">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="-0.432" y1="-0.356" x2="0.432" y2="-0.356" width="0.1524" layer="51"/>
<wire x1="0.432" y1="0.356" x2="-0.432" y2="0.356" width="0.1524" layer="51"/>
<smd name="1" x="-0.7" y="0" dx="0.8" dy="1.1" layer="1"/>
<smd name="2" x="0.7" y="0" dx="0.8" dy="1.1" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="0.4318" y1="-0.4318" x2="0.8382" y2="0.4318" layer="51"/>
<rectangle x1="-0.8382" y1="-0.4318" x2="-0.4318" y2="0.4318" layer="51"/>
</package>
<package name="R0805">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;</description>
<wire x1="-0.41" y1="0.635" x2="0.41" y2="0.635" width="0.1524" layer="51"/>
<wire x1="-0.41" y1="-0.635" x2="0.41" y2="-0.635" width="0.1524" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="1" dy="1.5" layer="1"/>
<smd name="2" x="0.75" y="0" dx="1" dy="1.5" layer="1"/>
<text x="-0.635" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="0.4064" y1="-0.6985" x2="1.0564" y2="0.7015" layer="51"/>
<rectangle x1="-1.0668" y1="-0.6985" x2="-0.4168" y2="0.7015" layer="51"/>
</package>
<package name="R1206">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="0.9525" y1="-0.8128" x2="-0.9652" y2="-0.8128" width="0.1524" layer="51"/>
<wire x1="0.9525" y1="0.8128" x2="-0.9652" y2="0.8128" width="0.1524" layer="51"/>
<smd name="2" x="1.4" y="0" dx="1.2" dy="1.803" layer="1"/>
<smd name="1" x="-1.4" y="0" dx="1.2" dy="1.803" layer="1"/>
<text x="-1.27" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.6891" y1="-0.8763" x2="-0.9525" y2="0.8763" layer="51"/>
<rectangle x1="0.9525" y1="-0.8763" x2="1.6891" y2="0.8763" layer="51"/>
</package>
<package name="C0402">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<smd name="1" x="-0.45" y="0" dx="0.6" dy="0.8" layer="1"/>
<smd name="2" x="0.45" y="0" dx="0.6" dy="0.8" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
</package>
<package name="C0603">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="1" x="-0.65" y="0" dx="0.9" dy="1.1" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.9" dy="1.1" layer="1"/>
<text x="-0.635" y="0.635" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="-1.905" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
</package>
<package name="C0805">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;</description>
<wire x1="-0.381" y1="0.66" x2="0.381" y2="0.66" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.66" x2="0.381" y2="-0.66" width="0.1016" layer="51"/>
<smd name="1" x="-0.8" y="0" dx="1.1" dy="1.5" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1.5" layer="1"/>
<text x="-1.27" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.0922" y1="-0.7239" x2="-0.3421" y2="0.7262" layer="51"/>
<rectangle x1="0.3556" y1="-0.7239" x2="1.1057" y2="0.7262" layer="51"/>
</package>
<package name="TSOT23-5">
<description>&lt;b&gt;S5 Package 5-Lead Plastic TSOT-23&lt;/b&gt;&lt;p&gt;
Source: http://cds.linear.com/docs/Datasheet/623012fb.pdf</description>
<wire x1="1.422" y1="-0.781" x2="-1.423" y2="-0.781" width="0.1524" layer="51"/>
<wire x1="-1.423" y1="0.781" x2="1.422" y2="0.781" width="0.1524" layer="51"/>
<smd name="1" x="-0.95" y="-1.3" dx="0.62" dy="1.22" layer="1"/>
<smd name="2" x="0" y="-1.3" dx="0.62" dy="1.22" layer="1"/>
<smd name="3" x="0.95" y="-1.3" dx="0.62" dy="1.22" layer="1"/>
<smd name="4" x="0.95" y="1.3" dx="0.62" dy="1.22" layer="1"/>
<smd name="5" x="-0.95" y="1.3" dx="0.62" dy="1.22" layer="1"/>
<text x="2.8575" y="-1.5875" size="1.016" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<text x="-1.5875" y="-1.5875" size="1.016" layer="25" ratio="10" rot="R90">&gt;NAME</text>
</package>
<package name="SMA">
<description>&lt;b&gt;SMA&lt;/b&gt; CASE 403D-02&lt;p&gt;
Source: http://www.onsemi.com/pub_link/Collateral/MBRA340T3-D.PDF</description>
<wire x1="2.25" y1="1.25" x2="2.25" y2="-1.25" width="0.254" layer="51"/>
<wire x1="-2.25" y1="-1.25" x2="-2.25" y2="1.25" width="0.254" layer="51"/>
<smd name="C" x="-2" y="0" dx="2" dy="2" layer="1"/>
<smd name="A" x="2" y="0" dx="2" dy="2" layer="1"/>
<text x="-2.75" y="2" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.75" y="-3.5" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="2.38" y1="-0.825" x2="2.8" y2="0.8" layer="51"/>
<rectangle x1="-2.8" y1="-0.8" x2="-2.38" y2="0.8" layer="51"/>
<rectangle x1="-1.5" y1="-1.75" x2="-0.75" y2="1.75" layer="51"/>
</package>
<package name="DO07">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 2.54 mm, horizontal, grid 10.16 mm</description>
<wire x1="5.08" y1="0" x2="4.191" y2="0" width="0.508" layer="51"/>
<wire x1="-5.08" y1="0" x2="-4.191" y2="0" width="0.508" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.302" y1="1.27" x2="3.556" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.556" y1="1.016" x2="-3.302" y2="1.27" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.556" y1="-1.016" x2="-3.302" y2="-1.27" width="0.1524" layer="21" curve="90"/>
<wire x1="3.302" y1="-1.27" x2="3.556" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="3.556" y1="-1.016" x2="3.556" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-3.556" y1="1.016" x2="-3.556" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="1.27" x2="3.302" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="-1.27" x2="3.302" y2="-1.27" width="0.1524" layer="21"/>
<pad name="C" x="-5.08" y="0" drill="0.8128" shape="long"/>
<pad name="A" x="5.08" y="0" drill="0.8128" shape="long"/>
<text x="-3.429" y="1.524" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.429" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.429" y1="-1.27" x2="-1.651" y2="1.27" layer="21"/>
<rectangle x1="3.556" y1="-0.254" x2="4.191" y2="0.254" layer="21"/>
<rectangle x1="-4.191" y1="-0.254" x2="-3.556" y2="0.254" layer="21"/>
</package>
<package name="SOT23-BEC">
<description>TO-236 ITT Intermetall</description>
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.6604" width="0.127" layer="51"/>
<wire x1="1.4224" y1="-0.6604" x2="-1.4224" y2="-0.6604" width="0.127" layer="51"/>
<wire x1="-1.4224" y1="-0.6604" x2="-1.4224" y2="0.6604" width="0.127" layer="51"/>
<wire x1="-1.4224" y1="0.6604" x2="1.4224" y2="0.6604" width="0.127" layer="51"/>
<smd name="C" x="0" y="1.1" dx="1" dy="1.4" layer="1"/>
<smd name="E" x="0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<smd name="B" x="-0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2286" y1="0.7112" x2="0.2286" y2="1.2954" layer="51"/>
<rectangle x1="0.7112" y1="-1.2954" x2="1.1684" y2="-0.7112" layer="51"/>
<rectangle x1="-1.1684" y1="-1.2954" x2="-0.7112" y2="-0.7112" layer="51"/>
</package>
<package name="TO92-EBC">
<description>&lt;b&gt;TO-92&lt;/b&gt;&lt;p&gt;
 grid 5.08 mm</description>
<wire x1="-2.095" y1="-2.921" x2="2.095" y2="-2.921" width="0.127" layer="21"/>
<wire x1="-2.413" y1="-0.1341" x2="2.413" y2="-0.1341" width="0.127" layer="21" curve="-129.583"/>
<wire x1="1.136" y1="-1.397" x2="-1.136" y2="-1.397" width="0.127" layer="51"/>
<wire x1="-2.413" y1="-0.1341" x2="-2.664" y2="-1.397" width="0.127" layer="51" curve="27.9376"/>
<wire x1="-2.664" y1="-1.397" x2="-2.413" y2="-2.4059" width="0.127" layer="51" curve="22.4788"/>
<wire x1="-1.404" y1="-1.397" x2="-2.664" y2="-1.397" width="0.127" layer="51"/>
<wire x1="-2.4135" y1="-2.4059" x2="-2.095" y2="-2.921" width="0.127" layer="21" curve="13.0385"/>
<wire x1="-1.136" y1="-1.397" x2="-1.404" y2="-1.397" width="0.127" layer="21"/>
<wire x1="2.413" y1="-2.4059" x2="2.664" y2="-1.397" width="0.127" layer="51" curve="22.4788"/>
<wire x1="2.664" y1="-1.397" x2="2.413" y2="-0.1341" width="0.127" layer="51" curve="27.9376"/>
<wire x1="2.664" y1="-1.397" x2="1.404" y2="-1.397" width="0.127" layer="51"/>
<wire x1="1.404" y1="-1.397" x2="1.136" y2="-1.397" width="0.127" layer="21"/>
<wire x1="2.095" y1="-2.921" x2="2.4247" y2="-2.3818" width="0.127" layer="21" curve="13.6094"/>
<pad name="C" x="-2.54" y="-1.27" drill="0.8128" shape="long" rot="R90"/>
<pad name="E" x="2.54" y="-1.27" drill="0.8128" shape="long" rot="R90"/>
<pad name="B" x="0" y="-1.27" drill="0.8128" shape="long" rot="R90"/>
<text x="-2.54" y="1.778" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-4.572" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SOT323-5L">
<wire x1="1.1" y1="-0.65" x2="-1.1" y2="-0.65" width="0.1524" layer="51"/>
<wire x1="-1.1" y1="0.65" x2="1.1" y2="0.65" width="0.1524" layer="51"/>
<smd name="1" x="-0.65" y="-0.95" dx="0.35" dy="1" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<smd name="2" x="0" y="-0.95" dx="0.35" dy="1" layer="1"/>
<smd name="3" x="0.65" y="-0.95" dx="0.35" dy="1" layer="1"/>
<smd name="4" x="0.65" y="0.95" dx="0.35" dy="1" layer="1"/>
<smd name="5" x="-0.65" y="0.95" dx="0.35" dy="1" layer="1"/>
</package>
<package name="QFN32">
<description>&lt;b&gt;32-Pin (5x5 mm) QFN&lt;/b&gt;&lt;p&gt;
Source: http://www.cypress.com .. 38-12025_0P_V.pdf</description>
<wire x1="-2.4" y1="2.15" x2="-2.15" y2="2.4" width="0.2032" layer="21"/>
<wire x1="-2.15" y1="2.4" x2="2.15" y2="2.4" width="0.2032" layer="51"/>
<wire x1="2.15" y1="2.4" x2="2.4" y2="2.15" width="0.2032" layer="21"/>
<wire x1="2.4" y1="2.15" x2="2.4" y2="-2.15" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-2.15" x2="2.15" y2="-2.4" width="0.2032" layer="21"/>
<wire x1="2.15" y1="-2.4" x2="-2.15" y2="-2.4" width="0.2032" layer="51"/>
<wire x1="-2.15" y1="-2.4" x2="-2.4" y2="-2.15" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="-2.15" x2="-2.4" y2="2.15" width="0.2032" layer="51"/>
<circle x="-2.6" y="2.6" radius="0.25" width="0" layer="51"/>
<smd name="31" x="-1.25" y="2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="32" x="-1.75" y="2.4" dx="0.7" dy="0.25" layer="1" roundness="100" rot="R270"/>
<text x="-2.5" y="3" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.5" y="-4.25" size="1.27" layer="27">&gt;VALUE</text>
<smd name="25" x="1.75" y="2.4" dx="0.7" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="26" x="1.25" y="2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="27" x="0.75" y="2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="28" x="0.25" y="2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="29" x="-0.25" y="2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="30" x="-0.75" y="2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R270"/>
<smd name="1" x="-2.4" y="1.75" dx="0.7" dy="0.25" layer="1" roundness="100"/>
<smd name="2" x="-2.35" y="1.25" dx="0.8" dy="0.25" layer="1" roundness="100"/>
<smd name="3" x="-2.35" y="0.75" dx="0.8" dy="0.25" layer="1" roundness="100"/>
<smd name="4" x="-2.35" y="0.25" dx="0.8" dy="0.25" layer="1" roundness="100"/>
<smd name="5" x="-2.35" y="-0.25" dx="0.8" dy="0.25" layer="1" roundness="100"/>
<smd name="6" x="-2.35" y="-0.75" dx="0.8" dy="0.25" layer="1" roundness="100"/>
<smd name="7" x="-2.35" y="-1.25" dx="0.8" dy="0.25" layer="1" roundness="100"/>
<smd name="8" x="-2.4" y="-1.75" dx="0.7" dy="0.25" layer="1" roundness="100"/>
<smd name="17" x="2.4" y="-1.75" dx="0.7" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="18" x="2.35" y="-1.25" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="19" x="2.35" y="-0.75" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="20" x="2.35" y="-0.25" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="21" x="2.35" y="0.25" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="22" x="2.35" y="0.75" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="23" x="2.35" y="1.25" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="24" x="2.4" y="1.75" dx="0.7" dy="0.25" layer="1" roundness="100" rot="R180"/>
<smd name="9" x="-1.75" y="-2.4" dx="0.7" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="10" x="-1.25" y="-2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="11" x="-0.75" y="-2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="12" x="-0.25" y="-2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="13" x="0.25" y="-2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="14" x="0.75" y="-2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="15" x="1.25" y="-2.35" dx="0.8" dy="0.25" layer="1" roundness="100" rot="R90"/>
<smd name="16" x="1.75" y="-2.4" dx="0.7" dy="0.25" layer="1" roundness="100" rot="R90"/>
<pad name="P$1" x="-1.1" y="1.1" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$2" x="0" y="1.1" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$3" x="1.1" y="1.1" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$4" x="-1.1" y="0" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$5" x="0" y="0" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$6" x="1.1" y="0" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$7" x="-1.1" y="-1.1" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$8" x="0" y="-1.1" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<pad name="P$9" x="1.1" y="-1.1" drill="0.4" diameter="1.1" shape="square" stop="no"/>
<rectangle x1="-1.65" y1="-1.65" x2="1.65" y2="1.65" layer="29"/>
<rectangle x1="-1.65" y1="-1.65" x2="1.65" y2="1.65" layer="30"/>
</package>
<package name="32005-201">
<description>&lt;b&gt;MINI USB-B R/A SMT W/ REAR&lt;/b&gt;&lt;p&gt;
Source: http://www.cypressindustries.com/pdf/32005-201.pdf</description>
<wire x1="-5.9182" y1="3.8416" x2="-3.6879" y2="3.8416" width="0.1016" layer="51"/>
<wire x1="-3.6879" y1="3.8416" x2="-3.6879" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="-3.6879" y1="4.8799" x2="-3.3245" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="-3.3245" y1="4.8799" x2="-3.3245" y2="4.4646" width="0.1016" layer="51"/>
<wire x1="-3.3245" y1="4.4646" x2="-2.7015" y2="4.4646" width="0.1016" layer="51"/>
<wire x1="-2.7015" y1="4.4646" x2="-2.7015" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="-2.7015" y1="4.8799" x2="-2.3093" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="-2.3093" y1="4.8799" x2="-2.3093" y2="3.8416" width="0.1016" layer="51"/>
<wire x1="2.8032" y1="3.8416" x2="0.7266" y2="3.8416" width="0.1016" layer="51"/>
<wire x1="0.519" y1="4.205" x2="2.907" y2="4.205" width="0.1016" layer="51"/>
<wire x1="2.907" y1="4.205" x2="3.4781" y2="3.6339" width="0.1016" layer="51" curve="-90"/>
<wire x1="2.8032" y1="3.8416" x2="3.0627" y2="3.5821" width="0.1016" layer="51" curve="-90"/>
<wire x1="3.0627" y1="3.5821" x2="3.0627" y2="3.011" width="0.1016" layer="51"/>
<wire x1="1.713" y1="4.2569" x2="1.713" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="1.713" y1="4.8799" x2="2.1283" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="2.1283" y1="4.8799" x2="2.1283" y2="4.4646" width="0.1016" layer="51"/>
<wire x1="2.1283" y1="4.4646" x2="2.6474" y2="4.4646" width="0.1016" layer="51"/>
<wire x1="2.6474" y1="4.4646" x2="2.6474" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="2.6474" y1="4.8799" x2="3.0627" y2="4.8799" width="0.1016" layer="51"/>
<wire x1="3.0627" y1="4.8799" x2="3.0627" y2="4.2569" width="0.1016" layer="51"/>
<wire x1="3.0627" y1="-1.9726" x2="3.0627" y2="1.9727" width="0.1016" layer="51"/>
<wire x1="-5.9182" y1="-3.8414" x2="-3.6879" y2="-3.8414" width="0.1016" layer="51"/>
<wire x1="-3.6879" y1="-3.8414" x2="-3.6879" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="-3.6879" y1="-4.8797" x2="-3.3245" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="-3.3245" y1="-4.8797" x2="-3.3245" y2="-4.4644" width="0.1016" layer="51"/>
<wire x1="-3.3245" y1="-4.4644" x2="-2.7015" y2="-4.4644" width="0.1016" layer="51"/>
<wire x1="-2.7015" y1="-4.4644" x2="-2.7015" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="-2.7015" y1="-4.8797" x2="-2.3093" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="-2.3093" y1="-4.8797" x2="-2.3093" y2="-3.8414" width="0.1016" layer="51"/>
<wire x1="-2.3093" y1="-3.8414" x2="2.8032" y2="-3.8414" width="0.1016" layer="51"/>
<wire x1="0.519" y1="-4.2048" x2="2.907" y2="-4.2048" width="0.1016" layer="51"/>
<wire x1="2.907" y1="-4.2048" x2="3.4781" y2="-3.6337" width="0.1016" layer="51" curve="90.020069"/>
<wire x1="2.8032" y1="-3.8414" x2="3.0627" y2="-3.5819" width="0.1016" layer="51" curve="90.044176"/>
<wire x1="3.0627" y1="-3.5819" x2="3.0627" y2="-3.0108" width="0.1016" layer="51"/>
<wire x1="1.713" y1="-4.2567" x2="1.713" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="1.713" y1="-4.8797" x2="2.1283" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="2.1283" y1="-4.8797" x2="2.1283" y2="-4.4644" width="0.1016" layer="51"/>
<wire x1="2.1283" y1="-4.4644" x2="2.6474" y2="-4.4644" width="0.1016" layer="51"/>
<wire x1="2.6474" y1="-4.4644" x2="2.6474" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="2.6474" y1="-4.8797" x2="3.0627" y2="-4.8797" width="0.1016" layer="51"/>
<wire x1="3.0627" y1="-4.8797" x2="3.0627" y2="-4.2567" width="0.1016" layer="51"/>
<wire x1="1.5573" y1="-1.9725" x2="1.5573" y2="2.0248" width="0.1016" layer="51"/>
<wire x1="-2.3093" y1="3.8416" x2="0.7265" y2="3.8415" width="0.1016" layer="51"/>
<wire x1="3.4781" y1="3.634" x2="3.478" y2="-3.0109" width="0.1016" layer="51"/>
<smd name="M1" x="-3" y="-4.45" dx="2.5" dy="2" layer="1"/>
<smd name="M2" x="-3" y="4.45" dx="2.5" dy="2" layer="1"/>
<smd name="M4" x="2.9" y="-4.45" dx="3.3" dy="2" layer="1"/>
<smd name="M3" x="2.9" y="4.45" dx="3.3" dy="2" layer="1"/>
<smd name="1" x="3" y="1.6" dx="3.1" dy="0.5" layer="1"/>
<smd name="2" x="3" y="0.8" dx="3.1" dy="0.5" layer="1"/>
<smd name="3" x="3" y="0" dx="3.1" dy="0.5" layer="1"/>
<smd name="4" x="3" y="-0.8" dx="3.1" dy="0.5" layer="1"/>
<smd name="5" x="3" y="-1.6" dx="3.1" dy="0.5" layer="1"/>
<text x="-4.445" y="5.715" size="1.27" layer="25">&gt;NAME</text>
<text x="-4.445" y="-6.985" size="1.27" layer="27">&gt;VALUE</text>
<hole x="0" y="2.2" drill="0.9"/>
<hole x="0" y="-2.2" drill="0.9"/>
</package>
<package name="QUARTZ_5MM">
<pad name="P$1" x="2.5" y="0" drill="0.7"/>
<pad name="P$2" x="-2.5" y="0" drill="0.7"/>
<wire x1="3" y1="2.5" x2="-3" y2="2.5" width="0.127" layer="51"/>
<wire x1="-3" y1="-2.5" x2="3" y2="-2.5" width="0.127" layer="51"/>
<wire x1="-3" y1="-2.5" x2="-3" y2="2.5" width="0.127" layer="51" curve="-180"/>
<wire x1="3" y1="2.5" x2="3" y2="-2.5" width="0.127" layer="51" curve="-180"/>
</package>
<package name="LGA14">
<smd name="13" x="-1" y="-2" dx="0.9" dy="0.55" layer="1"/>
<smd name="1" x="1" y="-2" dx="0.9" dy="0.55" layer="1"/>
<smd name="12" x="-1" y="-1.2" dx="0.9" dy="0.55" layer="1"/>
<smd name="2" x="1" y="-1.2" dx="0.9" dy="0.55" layer="1"/>
<smd name="11" x="-1" y="-0.4" dx="0.9" dy="0.55" layer="1"/>
<smd name="3" x="1" y="-0.4" dx="0.9" dy="0.55" layer="1"/>
<smd name="10" x="-1" y="0.4" dx="0.9" dy="0.55" layer="1"/>
<smd name="4" x="1" y="0.4" dx="0.9" dy="0.55" layer="1"/>
<smd name="9" x="-1" y="1.2" dx="0.9" dy="0.55" layer="1"/>
<smd name="5" x="1" y="1.2" dx="0.9" dy="0.55" layer="1"/>
<smd name="8" x="-1" y="2" dx="0.9" dy="0.55" layer="1"/>
<smd name="6" x="1" y="2" dx="0.9" dy="0.55" layer="1"/>
<smd name="14" x="0" y="-2" dx="0.9" dy="0.55" layer="1" rot="R90"/>
<smd name="7" x="0" y="2" dx="0.9" dy="0.55" layer="1" rot="R90"/>
<polygon width="0.0634" layer="1">
<vertex x="1.6207" y="-2.9288"/>
<vertex x="1.9382" y="-2.9288"/>
<vertex x="1.9382" y="-2.6113"/>
<vertex x="1.6207" y="-2.6113"/>
</polygon>
<text x="0.35" y="-2.2" size="0.5" layer="27" rot="R90">&gt;VALUE</text>
<text x="2.54" y="-2.2" size="0.7" layer="25" rot="R90">&gt;NAME</text>
</package>
<package name="SOT23-5L">
<description>&lt;b&gt;Small Outline Transistor&lt;/b&gt;&lt;p&gt;
package type OT</description>
<wire x1="1.422" y1="0.81" x2="1.422" y2="-0.81" width="0.1524" layer="21"/>
<wire x1="1.422" y1="-0.81" x2="-1.422" y2="-0.81" width="0.1524" layer="51"/>
<wire x1="-1.422" y1="-0.81" x2="-1.422" y2="0.81" width="0.1524" layer="21"/>
<wire x1="-1.422" y1="0.81" x2="1.422" y2="0.81" width="0.1524" layer="51"/>
<wire x1="-0.522" y1="0.81" x2="0.522" y2="0.81" width="0.1524" layer="21"/>
<wire x1="-0.428" y1="-0.81" x2="-0.522" y2="-0.81" width="0.1524" layer="21"/>
<wire x1="0.522" y1="-0.81" x2="0.428" y2="-0.81" width="0.1524" layer="21"/>
<wire x1="-1.328" y1="-0.81" x2="-1.422" y2="-0.81" width="0.1524" layer="21"/>
<wire x1="1.422" y1="-0.81" x2="1.328" y2="-0.81" width="0.1524" layer="21"/>
<wire x1="1.328" y1="0.81" x2="1.422" y2="0.81" width="0.1524" layer="21"/>
<wire x1="-1.422" y1="0.81" x2="-1.328" y2="0.81" width="0.1524" layer="21"/>
<smd name="1" x="-0.95" y="-1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="2" x="0" y="-1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="3" x="0.95" y="-1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="4" x="0.95" y="1.3" dx="0.55" dy="1.2" layer="1"/>
<smd name="5" x="-0.95" y="1.3" dx="0.55" dy="1.2" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.429" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.2" y1="-1.5" x2="-0.7" y2="-0.85" layer="51"/>
<rectangle x1="-0.25" y1="-1.5" x2="0.25" y2="-0.85" layer="51"/>
<rectangle x1="0.7" y1="-1.5" x2="1.2" y2="-0.85" layer="51"/>
<rectangle x1="0.7" y1="0.85" x2="1.2" y2="1.5" layer="51"/>
<rectangle x1="-1.2" y1="0.85" x2="-0.7" y2="1.5" layer="51"/>
</package>
<package name="LQFP176">
<description>&lt;b&gt;LQFP176&lt;/b&gt;&lt;p&gt;
Auto generated by &lt;i&gt;make-symbol-device-package-bsdl.ulp Rev. 43&lt;/i&gt;&lt;br&gt;</description>
<smd name="1" x="-12.75" y="10.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="10.6" x2="-12" y2="10.9" layer="51"/>
<smd name="2" x="-12.75" y="10.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="10.1" x2="-12" y2="10.4" layer="51"/>
<smd name="3" x="-12.75" y="9.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="9.6" x2="-12" y2="9.9" layer="51"/>
<smd name="4" x="-12.75" y="9.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="9.1" x2="-12" y2="9.4" layer="51"/>
<smd name="5" x="-12.75" y="8.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="8.6" x2="-12" y2="8.9" layer="51"/>
<smd name="6" x="-12.75" y="8.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="8.1" x2="-12" y2="8.4" layer="51"/>
<smd name="7" x="-12.75" y="7.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="7.6" x2="-12" y2="7.9" layer="51"/>
<smd name="8" x="-12.75" y="7.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="7.1" x2="-12" y2="7.4" layer="51"/>
<smd name="9" x="-12.75" y="6.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="6.6" x2="-12" y2="6.9" layer="51"/>
<smd name="10" x="-12.75" y="6.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="6.1" x2="-12" y2="6.4" layer="51"/>
<smd name="11" x="-12.75" y="5.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="5.6" x2="-12" y2="5.9" layer="51"/>
<smd name="12" x="-12.75" y="5.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="5.1" x2="-12" y2="5.4" layer="51"/>
<smd name="13" x="-12.75" y="4.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="4.6" x2="-12" y2="4.9" layer="51"/>
<smd name="14" x="-12.75" y="4.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="4.1" x2="-12" y2="4.4" layer="51"/>
<smd name="15" x="-12.75" y="3.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="3.6" x2="-12" y2="3.9" layer="51"/>
<smd name="16" x="-12.75" y="3.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="3.1" x2="-12" y2="3.4" layer="51"/>
<smd name="17" x="-12.75" y="2.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="2.6" x2="-12" y2="2.9" layer="51"/>
<smd name="18" x="-12.75" y="2.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="2.1" x2="-12" y2="2.4" layer="51"/>
<smd name="19" x="-12.75" y="1.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="1.6" x2="-12" y2="1.9" layer="51"/>
<smd name="20" x="-12.75" y="1.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="1.1" x2="-12" y2="1.4" layer="51"/>
<smd name="21" x="-12.75" y="0.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="0.6" x2="-12" y2="0.9" layer="51"/>
<smd name="22" x="-12.75" y="0.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="0.1" x2="-12" y2="0.4" layer="51"/>
<smd name="23" x="-12.75" y="-0.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-0.4" x2="-12" y2="-0.1" layer="51"/>
<smd name="24" x="-12.75" y="-0.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-0.9" x2="-12" y2="-0.6" layer="51"/>
<smd name="25" x="-12.75" y="-1.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-1.4" x2="-12" y2="-1.1" layer="51"/>
<smd name="26" x="-12.75" y="-1.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-1.9" x2="-12" y2="-1.6" layer="51"/>
<smd name="27" x="-12.75" y="-2.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-2.4" x2="-12" y2="-2.1" layer="51"/>
<smd name="28" x="-12.75" y="-2.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-2.9" x2="-12" y2="-2.6" layer="51"/>
<smd name="29" x="-12.75" y="-3.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-3.4" x2="-12" y2="-3.1" layer="51"/>
<smd name="30" x="-12.75" y="-3.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-3.9" x2="-12" y2="-3.6" layer="51"/>
<smd name="31" x="-12.75" y="-4.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-4.4" x2="-12" y2="-4.1" layer="51"/>
<smd name="32" x="-12.75" y="-4.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-4.9" x2="-12" y2="-4.6" layer="51"/>
<smd name="33" x="-12.75" y="-5.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-5.4" x2="-12" y2="-5.1" layer="51"/>
<smd name="34" x="-12.75" y="-5.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-5.9" x2="-12" y2="-5.6" layer="51"/>
<smd name="35" x="-12.75" y="-6.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-6.4" x2="-12" y2="-6.1" layer="51"/>
<smd name="36" x="-12.75" y="-6.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-6.9" x2="-12" y2="-6.6" layer="51"/>
<smd name="37" x="-12.75" y="-7.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-7.4" x2="-12" y2="-7.1" layer="51"/>
<smd name="38" x="-12.75" y="-7.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-7.9" x2="-12" y2="-7.6" layer="51"/>
<smd name="39" x="-12.75" y="-8.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-8.4" x2="-12" y2="-8.1" layer="51"/>
<smd name="40" x="-12.75" y="-8.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-8.9" x2="-12" y2="-8.6" layer="51"/>
<smd name="41" x="-12.75" y="-9.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-9.4" x2="-12" y2="-9.1" layer="51"/>
<smd name="42" x="-12.75" y="-9.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-9.9" x2="-12" y2="-9.6" layer="51"/>
<smd name="43" x="-12.75" y="-10.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-10.4" x2="-12" y2="-10.1" layer="51"/>
<smd name="44" x="-12.75" y="-10.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="-13.35" y1="-10.9" x2="-12" y2="-10.6" layer="51"/>
<smd name="45" x="-10.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-10.9" y1="-13.35" x2="-10.6" y2="-12" layer="51"/>
<smd name="46" x="-10.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-10.4" y1="-13.35" x2="-10.1" y2="-12" layer="51"/>
<smd name="47" x="-9.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-9.9" y1="-13.35" x2="-9.6" y2="-12" layer="51"/>
<smd name="48" x="-9.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-9.4" y1="-13.35" x2="-9.1" y2="-12" layer="51"/>
<smd name="49" x="-8.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-8.9" y1="-13.35" x2="-8.6" y2="-12" layer="51"/>
<smd name="50" x="-8.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-8.4" y1="-13.35" x2="-8.1" y2="-12" layer="51"/>
<smd name="51" x="-7.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-7.9" y1="-13.35" x2="-7.6" y2="-12" layer="51"/>
<smd name="52" x="-7.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-7.4" y1="-13.35" x2="-7.1" y2="-12" layer="51"/>
<smd name="53" x="-6.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-6.9" y1="-13.35" x2="-6.6" y2="-12" layer="51"/>
<smd name="54" x="-6.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-6.4" y1="-13.35" x2="-6.1" y2="-12" layer="51"/>
<smd name="55" x="-5.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-5.9" y1="-13.35" x2="-5.6" y2="-12" layer="51"/>
<smd name="56" x="-5.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-5.4" y1="-13.35" x2="-5.1" y2="-12" layer="51"/>
<smd name="57" x="-4.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-4.9" y1="-13.35" x2="-4.6" y2="-12" layer="51"/>
<smd name="58" x="-4.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-4.4" y1="-13.35" x2="-4.1" y2="-12" layer="51"/>
<smd name="59" x="-3.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-3.9" y1="-13.35" x2="-3.6" y2="-12" layer="51"/>
<smd name="60" x="-3.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-3.4" y1="-13.35" x2="-3.1" y2="-12" layer="51"/>
<smd name="61" x="-2.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-2.9" y1="-13.35" x2="-2.6" y2="-12" layer="51"/>
<smd name="62" x="-2.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-2.4" y1="-13.35" x2="-2.1" y2="-12" layer="51"/>
<smd name="63" x="-1.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-1.9" y1="-13.35" x2="-1.6" y2="-12" layer="51"/>
<smd name="64" x="-1.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-1.4" y1="-13.35" x2="-1.1" y2="-12" layer="51"/>
<smd name="65" x="-0.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-0.9" y1="-13.35" x2="-0.6" y2="-12" layer="51"/>
<smd name="66" x="-0.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-0.4" y1="-13.35" x2="-0.1" y2="-12" layer="51"/>
<smd name="67" x="0.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="0.1" y1="-13.35" x2="0.4" y2="-12" layer="51"/>
<smd name="68" x="0.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="0.6" y1="-13.35" x2="0.9" y2="-12" layer="51"/>
<smd name="69" x="1.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="1.1" y1="-13.35" x2="1.4" y2="-12" layer="51"/>
<smd name="70" x="1.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="1.6" y1="-13.35" x2="1.9" y2="-12" layer="51"/>
<smd name="71" x="2.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="2.1" y1="-13.35" x2="2.4" y2="-12" layer="51"/>
<smd name="72" x="2.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="2.6" y1="-13.35" x2="2.9" y2="-12" layer="51"/>
<smd name="73" x="3.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="3.1" y1="-13.35" x2="3.4" y2="-12" layer="51"/>
<smd name="74" x="3.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="3.6" y1="-13.35" x2="3.9" y2="-12" layer="51"/>
<smd name="75" x="4.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="4.1" y1="-13.35" x2="4.4" y2="-12" layer="51"/>
<smd name="76" x="4.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="4.6" y1="-13.35" x2="4.9" y2="-12" layer="51"/>
<smd name="77" x="5.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="5.1" y1="-13.35" x2="5.4" y2="-12" layer="51"/>
<smd name="78" x="5.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="5.6" y1="-13.35" x2="5.9" y2="-12" layer="51"/>
<smd name="79" x="6.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="6.1" y1="-13.35" x2="6.4" y2="-12" layer="51"/>
<smd name="80" x="6.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="6.6" y1="-13.35" x2="6.9" y2="-12" layer="51"/>
<smd name="81" x="7.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="7.1" y1="-13.35" x2="7.4" y2="-12" layer="51"/>
<smd name="82" x="7.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="7.6" y1="-13.35" x2="7.9" y2="-12" layer="51"/>
<smd name="83" x="8.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="8.1" y1="-13.35" x2="8.4" y2="-12" layer="51"/>
<smd name="84" x="8.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="8.6" y1="-13.35" x2="8.9" y2="-12" layer="51"/>
<smd name="85" x="9.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="9.1" y1="-13.35" x2="9.4" y2="-12" layer="51"/>
<smd name="86" x="9.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="9.6" y1="-13.35" x2="9.9" y2="-12" layer="51"/>
<smd name="87" x="10.25" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="10.1" y1="-13.35" x2="10.4" y2="-12" layer="51"/>
<smd name="88" x="10.75" y="-12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="10.6" y1="-13.35" x2="10.9" y2="-12" layer="51"/>
<smd name="89" x="12.75" y="-10.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-10.9" x2="13.35" y2="-10.6" layer="51"/>
<smd name="90" x="12.75" y="-10.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-10.4" x2="13.35" y2="-10.1" layer="51"/>
<smd name="91" x="12.75" y="-9.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-9.9" x2="13.35" y2="-9.6" layer="51"/>
<smd name="92" x="12.75" y="-9.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-9.4" x2="13.35" y2="-9.1" layer="51"/>
<smd name="93" x="12.75" y="-8.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-8.9" x2="13.35" y2="-8.6" layer="51"/>
<smd name="94" x="12.75" y="-8.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-8.4" x2="13.35" y2="-8.1" layer="51"/>
<smd name="95" x="12.75" y="-7.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-7.9" x2="13.35" y2="-7.6" layer="51"/>
<smd name="96" x="12.75" y="-7.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-7.4" x2="13.35" y2="-7.1" layer="51"/>
<smd name="97" x="12.75" y="-6.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-6.9" x2="13.35" y2="-6.6" layer="51"/>
<smd name="98" x="12.75" y="-6.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-6.4" x2="13.35" y2="-6.1" layer="51"/>
<smd name="99" x="12.75" y="-5.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-5.9" x2="13.35" y2="-5.6" layer="51"/>
<smd name="100" x="12.75" y="-5.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-5.4" x2="13.35" y2="-5.1" layer="51"/>
<smd name="101" x="12.75" y="-4.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-4.9" x2="13.35" y2="-4.6" layer="51"/>
<smd name="102" x="12.75" y="-4.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-4.4" x2="13.35" y2="-4.1" layer="51"/>
<smd name="103" x="12.75" y="-3.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-3.9" x2="13.35" y2="-3.6" layer="51"/>
<smd name="104" x="12.75" y="-3.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-3.4" x2="13.35" y2="-3.1" layer="51"/>
<smd name="105" x="12.75" y="-2.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-2.9" x2="13.35" y2="-2.6" layer="51"/>
<smd name="106" x="12.75" y="-2.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-2.4" x2="13.35" y2="-2.1" layer="51"/>
<smd name="107" x="12.75" y="-1.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-1.9" x2="13.35" y2="-1.6" layer="51"/>
<smd name="108" x="12.75" y="-1.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-1.4" x2="13.35" y2="-1.1" layer="51"/>
<smd name="109" x="12.75" y="-0.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-0.9" x2="13.35" y2="-0.6" layer="51"/>
<smd name="110" x="12.75" y="-0.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="-0.4" x2="13.35" y2="-0.1" layer="51"/>
<smd name="111" x="12.75" y="0.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="0.1" x2="13.35" y2="0.4" layer="51"/>
<smd name="112" x="12.75" y="0.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="0.6" x2="13.35" y2="0.9" layer="51"/>
<smd name="113" x="12.75" y="1.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="1.1" x2="13.35" y2="1.4" layer="51"/>
<smd name="114" x="12.75" y="1.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="1.6" x2="13.35" y2="1.9" layer="51"/>
<smd name="115" x="12.75" y="2.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="2.1" x2="13.35" y2="2.4" layer="51"/>
<smd name="116" x="12.75" y="2.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="2.6" x2="13.35" y2="2.9" layer="51"/>
<smd name="117" x="12.75" y="3.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="3.1" x2="13.35" y2="3.4" layer="51"/>
<smd name="118" x="12.75" y="3.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="3.6" x2="13.35" y2="3.9" layer="51"/>
<smd name="119" x="12.75" y="4.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="4.1" x2="13.35" y2="4.4" layer="51"/>
<smd name="120" x="12.75" y="4.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="4.6" x2="13.35" y2="4.9" layer="51"/>
<smd name="121" x="12.75" y="5.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="5.1" x2="13.35" y2="5.4" layer="51"/>
<smd name="122" x="12.75" y="5.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="5.6" x2="13.35" y2="5.9" layer="51"/>
<smd name="123" x="12.75" y="6.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="6.1" x2="13.35" y2="6.4" layer="51"/>
<smd name="124" x="12.75" y="6.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="6.6" x2="13.35" y2="6.9" layer="51"/>
<smd name="125" x="12.75" y="7.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="7.1" x2="13.35" y2="7.4" layer="51"/>
<smd name="126" x="12.75" y="7.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="7.6" x2="13.35" y2="7.9" layer="51"/>
<smd name="127" x="12.75" y="8.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="8.1" x2="13.35" y2="8.4" layer="51"/>
<smd name="128" x="12.75" y="8.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="8.6" x2="13.35" y2="8.9" layer="51"/>
<smd name="129" x="12.75" y="9.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="9.1" x2="13.35" y2="9.4" layer="51"/>
<smd name="130" x="12.75" y="9.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="9.6" x2="13.35" y2="9.9" layer="51"/>
<smd name="131" x="12.75" y="10.25" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="10.1" x2="13.35" y2="10.4" layer="51"/>
<smd name="132" x="12.75" y="10.75" dx="1.2" dy="0.26" layer="1"/>
<rectangle x1="12" y1="10.6" x2="13.35" y2="10.9" layer="51"/>
<smd name="133" x="10.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="10.6" y1="12" x2="10.9" y2="13.35" layer="51"/>
<smd name="134" x="10.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="10.1" y1="12" x2="10.4" y2="13.35" layer="51"/>
<smd name="135" x="9.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="9.6" y1="12" x2="9.9" y2="13.35" layer="51"/>
<smd name="136" x="9.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="9.1" y1="12" x2="9.4" y2="13.35" layer="51"/>
<smd name="137" x="8.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="8.6" y1="12" x2="8.9" y2="13.35" layer="51"/>
<smd name="138" x="8.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="8.1" y1="12" x2="8.4" y2="13.35" layer="51"/>
<smd name="139" x="7.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="7.6" y1="12" x2="7.9" y2="13.35" layer="51"/>
<smd name="140" x="7.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="7.1" y1="12" x2="7.4" y2="13.35" layer="51"/>
<smd name="141" x="6.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="6.6" y1="12" x2="6.9" y2="13.35" layer="51"/>
<smd name="142" x="6.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="6.1" y1="12" x2="6.4" y2="13.35" layer="51"/>
<smd name="143" x="5.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="5.6" y1="12" x2="5.9" y2="13.35" layer="51"/>
<smd name="144" x="5.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="5.1" y1="12" x2="5.4" y2="13.35" layer="51"/>
<smd name="145" x="4.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="4.6" y1="12" x2="4.9" y2="13.35" layer="51"/>
<smd name="146" x="4.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="4.1" y1="12" x2="4.4" y2="13.35" layer="51"/>
<smd name="147" x="3.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="3.6" y1="12" x2="3.9" y2="13.35" layer="51"/>
<smd name="148" x="3.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="3.1" y1="12" x2="3.4" y2="13.35" layer="51"/>
<smd name="149" x="2.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="2.6" y1="12" x2="2.9" y2="13.35" layer="51"/>
<smd name="150" x="2.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="2.1" y1="12" x2="2.4" y2="13.35" layer="51"/>
<smd name="151" x="1.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="1.6" y1="12" x2="1.9" y2="13.35" layer="51"/>
<smd name="152" x="1.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="1.1" y1="12" x2="1.4" y2="13.35" layer="51"/>
<smd name="153" x="0.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="0.6" y1="12" x2="0.9" y2="13.35" layer="51"/>
<smd name="154" x="0.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="0.1" y1="12" x2="0.4" y2="13.35" layer="51"/>
<smd name="155" x="-0.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-0.4" y1="12" x2="-0.1" y2="13.35" layer="51"/>
<smd name="156" x="-0.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-0.9" y1="12" x2="-0.6" y2="13.35" layer="51"/>
<smd name="157" x="-1.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-1.4" y1="12" x2="-1.1" y2="13.35" layer="51"/>
<smd name="158" x="-1.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-1.9" y1="12" x2="-1.6" y2="13.35" layer="51"/>
<smd name="159" x="-2.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-2.4" y1="12" x2="-2.1" y2="13.35" layer="51"/>
<smd name="160" x="-2.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-2.9" y1="12" x2="-2.6" y2="13.35" layer="51"/>
<smd name="161" x="-3.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-3.4" y1="12" x2="-3.1" y2="13.35" layer="51"/>
<smd name="162" x="-3.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-3.9" y1="12" x2="-3.6" y2="13.35" layer="51"/>
<smd name="163" x="-4.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-4.4" y1="12" x2="-4.1" y2="13.35" layer="51"/>
<smd name="164" x="-4.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-4.9" y1="12" x2="-4.6" y2="13.35" layer="51"/>
<smd name="165" x="-5.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-5.4" y1="12" x2="-5.1" y2="13.35" layer="51"/>
<smd name="166" x="-5.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-5.9" y1="12" x2="-5.6" y2="13.35" layer="51"/>
<smd name="167" x="-6.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-6.4" y1="12" x2="-6.1" y2="13.35" layer="51"/>
<smd name="168" x="-6.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-6.9" y1="12" x2="-6.6" y2="13.35" layer="51"/>
<smd name="169" x="-7.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-7.4" y1="12" x2="-7.1" y2="13.35" layer="51"/>
<smd name="170" x="-7.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-7.9" y1="12" x2="-7.6" y2="13.35" layer="51"/>
<smd name="171" x="-8.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-8.4" y1="12" x2="-8.1" y2="13.35" layer="51"/>
<smd name="172" x="-8.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-8.9" y1="12" x2="-8.6" y2="13.35" layer="51"/>
<smd name="173" x="-9.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-9.4" y1="12" x2="-9.1" y2="13.35" layer="51"/>
<smd name="174" x="-9.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-9.9" y1="12" x2="-9.6" y2="13.35" layer="51"/>
<smd name="175" x="-10.25" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-10.4" y1="12" x2="-10.1" y2="13.35" layer="51"/>
<smd name="176" x="-10.75" y="12.75" dx="0.26" dy="1.2" layer="1"/>
<rectangle x1="-10.9" y1="12" x2="-10.6" y2="13.35" layer="51"/>
<wire x1="-11.8984" y1="11.4" x2="-11.4" y2="11.8984" width="0.2032" layer="21"/>
<wire x1="-11.8984" y1="-11.8984" x2="11.8984" y2="-11.8984" width="0.2032" layer="21"/>
<wire x1="11.8984" y1="-11.8984" x2="11.8984" y2="11.8984" width="0.2032" layer="21"/>
<wire x1="11.8984" y1="11.8984" x2="-11.8984" y2="11.8984" width="0.2032" layer="21"/>
<wire x1="-11.8984" y1="11.8984" x2="-11.8984" y2="-11.8984" width="0.2032" layer="21"/>
<text x="-13.35" y="13.985" size="1.27" layer="25">&gt;NAME</text>
<text x="-13.35" y="-15.255" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-13.35" y1="10.6" x2="-12" y2="10.9" layer="51"/>
<circle x="-12.5" y="12.5" radius="0.15" width="0.3" layer="1"/>
</package>
<package name="NOKIA1100_KEY_PAD_0">
<smd name="OUTER" x="0" y="2" dx="1.2" dy="1.2" layer="1" roundness="100" rot="R90" stop="no" thermals="no" cream="no"/>
<smd name="OUTER1" x="0" y="-2" dx="1.2" dy="1.2" layer="1" roundness="100" rot="R90" stop="no" thermals="no" cream="no"/>
<circle x="0" y="0" radius="0.4" width="1" layer="29"/>
<smd name="INNER" x="0" y="0" dx="1.8" dy="1.8" layer="1" roundness="100" stop="no" thermals="no" cream="no"/>
<wire x1="-2" y1="0" x2="0" y2="-2" width="1.4" layer="1" curve="-270"/>
<wire x1="-2" y1="0" x2="0" y2="-2" width="1.6" layer="29" curve="-270"/>
<wire x1="-1.1" y1="0" x2="0" y2="-1.1" width="0.5" layer="29" curve="-270"/>
<wire x1="0" y1="0" x2="-1.4" y2="-1.4" width="0.6" layer="1"/>
</package>
<package name="SMC_A">
<description>&lt;b&gt;Chip Capacitor &lt;/b&gt; Polar tantalum capacitors with solid electrolyte&lt;p&gt;
Siemens Matsushita Components B 45 194, B 45 197, B 45 198&lt;br&gt;
Source: www.farnell.com/datasheets/247.pdf</description>
<wire x1="-1.45" y1="0.75" x2="1.45" y2="0.75" width="0.1016" layer="51"/>
<wire x1="1.45" y1="0.75" x2="1.45" y2="-0.75" width="0.1016" layer="51"/>
<wire x1="1.45" y1="-0.75" x2="-1.45" y2="-0.75" width="0.1016" layer="51"/>
<wire x1="-1.45" y1="-0.75" x2="-1.45" y2="0.75" width="0.1016" layer="51"/>
<smd name="+" x="-1.5" y="0" dx="0.8" dy="1.4" layer="1"/>
<smd name="-" x="1.5" y="0" dx="0.8" dy="1.4" layer="1" rot="R180"/>
<text x="-1.6" y="0.975" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.6" y="-2" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-1.6" y1="-0.6" x2="-1.4" y2="0.6" layer="51"/>
<rectangle x1="1.4" y1="-0.6" x2="1.6" y2="0.6" layer="51" rot="R180"/>
<rectangle x1="-1.45" y1="-0.75" x2="-0.8" y2="0.75" layer="51"/>
</package>
<package name="LQFP100">
<description>&lt;b&gt;LQFP100&lt;/b&gt;&lt;p&gt;
Auto generated by &lt;i&gt;make-symbol-device-package-bsdl.ulp Rev. 43&lt;/i&gt;&lt;br&gt;</description>
<smd name="1" x="-7.75" y="6" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="5.85" x2="-7" y2="6.15" layer="51"/>
<smd name="2" x="-7.75" y="5.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="5.35" x2="-7" y2="5.65" layer="51"/>
<smd name="3" x="-7.75" y="5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="4.85" x2="-7" y2="5.15" layer="51"/>
<smd name="4" x="-7.75" y="4.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="4.35" x2="-7" y2="4.65" layer="51"/>
<smd name="5" x="-7.75" y="4" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="3.85" x2="-7" y2="4.15" layer="51"/>
<smd name="6" x="-7.75" y="3.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="3.35" x2="-7" y2="3.65" layer="51"/>
<smd name="7" x="-7.75" y="3" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="2.85" x2="-7" y2="3.15" layer="51"/>
<smd name="8" x="-7.75" y="2.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="2.35" x2="-7" y2="2.65" layer="51"/>
<smd name="9" x="-7.75" y="2" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="1.85" x2="-7" y2="2.15" layer="51"/>
<smd name="10" x="-7.75" y="1.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="1.35" x2="-7" y2="1.65" layer="51"/>
<smd name="11" x="-7.75" y="1" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="0.85" x2="-7" y2="1.15" layer="51"/>
<smd name="12" x="-7.75" y="0.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="0.35" x2="-7" y2="0.65" layer="51"/>
<smd name="13" x="-7.75" y="0" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-0.15" x2="-7" y2="0.15" layer="51"/>
<smd name="14" x="-7.75" y="-0.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-0.65" x2="-7" y2="-0.35" layer="51"/>
<smd name="15" x="-7.75" y="-1" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-1.15" x2="-7" y2="-0.85" layer="51"/>
<smd name="16" x="-7.75" y="-1.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-1.65" x2="-7" y2="-1.35" layer="51"/>
<smd name="17" x="-7.75" y="-2" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-2.15" x2="-7" y2="-1.85" layer="51"/>
<smd name="18" x="-7.75" y="-2.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-2.65" x2="-7" y2="-2.35" layer="51"/>
<smd name="19" x="-7.75" y="-3" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-3.15" x2="-7" y2="-2.85" layer="51"/>
<smd name="20" x="-7.75" y="-3.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-3.65" x2="-7" y2="-3.35" layer="51"/>
<smd name="21" x="-7.75" y="-4" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-4.15" x2="-7" y2="-3.85" layer="51"/>
<smd name="22" x="-7.75" y="-4.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-4.65" x2="-7" y2="-4.35" layer="51"/>
<smd name="23" x="-7.75" y="-5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-5.15" x2="-7" y2="-4.85" layer="51"/>
<smd name="24" x="-7.75" y="-5.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-5.65" x2="-7" y2="-5.35" layer="51"/>
<smd name="25" x="-7.75" y="-6" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="-8.35" y1="-6.15" x2="-7" y2="-5.85" layer="51"/>
<smd name="26" x="-6" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-6.15" y1="-8.35" x2="-5.85" y2="-7" layer="51"/>
<smd name="27" x="-5.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-5.65" y1="-8.35" x2="-5.35" y2="-7" layer="51"/>
<smd name="28" x="-5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-5.15" y1="-8.35" x2="-4.85" y2="-7" layer="51"/>
<smd name="29" x="-4.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-4.65" y1="-8.35" x2="-4.35" y2="-7" layer="51"/>
<smd name="30" x="-4" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-4.15" y1="-8.35" x2="-3.85" y2="-7" layer="51"/>
<smd name="31" x="-3.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-3.65" y1="-8.35" x2="-3.35" y2="-7" layer="51"/>
<smd name="32" x="-3" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-3.15" y1="-8.35" x2="-2.85" y2="-7" layer="51"/>
<smd name="33" x="-2.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-2.65" y1="-8.35" x2="-2.35" y2="-7" layer="51"/>
<smd name="34" x="-2" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-2.15" y1="-8.35" x2="-1.85" y2="-7" layer="51"/>
<smd name="35" x="-1.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-1.65" y1="-8.35" x2="-1.35" y2="-7" layer="51"/>
<smd name="36" x="-1" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-1.15" y1="-8.35" x2="-0.85" y2="-7" layer="51"/>
<smd name="37" x="-0.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-0.65" y1="-8.35" x2="-0.35" y2="-7" layer="51"/>
<smd name="38" x="0" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-0.15" y1="-8.35" x2="0.15" y2="-7" layer="51"/>
<smd name="39" x="0.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="0.35" y1="-8.35" x2="0.65" y2="-7" layer="51"/>
<smd name="40" x="1" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="0.85" y1="-8.35" x2="1.15" y2="-7" layer="51"/>
<smd name="41" x="1.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="1.35" y1="-8.35" x2="1.65" y2="-7" layer="51"/>
<smd name="42" x="2" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="1.85" y1="-8.35" x2="2.15" y2="-7" layer="51"/>
<smd name="43" x="2.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="2.35" y1="-8.35" x2="2.65" y2="-7" layer="51"/>
<smd name="44" x="3" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="2.85" y1="-8.35" x2="3.15" y2="-7" layer="51"/>
<smd name="45" x="3.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="3.35" y1="-8.35" x2="3.65" y2="-7" layer="51"/>
<smd name="46" x="4" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="3.85" y1="-8.35" x2="4.15" y2="-7" layer="51"/>
<smd name="47" x="4.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="4.35" y1="-8.35" x2="4.65" y2="-7" layer="51"/>
<smd name="48" x="5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="4.85" y1="-8.35" x2="5.15" y2="-7" layer="51"/>
<smd name="49" x="5.5" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="5.35" y1="-8.35" x2="5.65" y2="-7" layer="51"/>
<smd name="50" x="6" y="-7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="5.85" y1="-8.35" x2="6.15" y2="-7" layer="51"/>
<smd name="51" x="7.75" y="-6" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-6.15" x2="8.35" y2="-5.85" layer="51"/>
<smd name="52" x="7.75" y="-5.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-5.65" x2="8.35" y2="-5.35" layer="51"/>
<smd name="53" x="7.75" y="-5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-5.15" x2="8.35" y2="-4.85" layer="51"/>
<smd name="54" x="7.75" y="-4.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-4.65" x2="8.35" y2="-4.35" layer="51"/>
<smd name="55" x="7.75" y="-4" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-4.15" x2="8.35" y2="-3.85" layer="51"/>
<smd name="56" x="7.75" y="-3.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-3.65" x2="8.35" y2="-3.35" layer="51"/>
<smd name="57" x="7.75" y="-3" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-3.15" x2="8.35" y2="-2.85" layer="51"/>
<smd name="58" x="7.75" y="-2.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-2.65" x2="8.35" y2="-2.35" layer="51"/>
<smd name="59" x="7.75" y="-2" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-2.15" x2="8.35" y2="-1.85" layer="51"/>
<smd name="60" x="7.75" y="-1.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-1.65" x2="8.35" y2="-1.35" layer="51"/>
<smd name="61" x="7.75" y="-1" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-1.15" x2="8.35" y2="-0.85" layer="51"/>
<smd name="62" x="7.75" y="-0.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-0.65" x2="8.35" y2="-0.35" layer="51"/>
<smd name="63" x="7.75" y="0" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="-0.15" x2="8.35" y2="0.15" layer="51"/>
<smd name="64" x="7.75" y="0.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="0.35" x2="8.35" y2="0.65" layer="51"/>
<smd name="65" x="7.75" y="1" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="0.85" x2="8.35" y2="1.15" layer="51"/>
<smd name="66" x="7.75" y="1.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="1.35" x2="8.35" y2="1.65" layer="51"/>
<smd name="67" x="7.75" y="2" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="1.85" x2="8.35" y2="2.15" layer="51"/>
<smd name="68" x="7.75" y="2.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="2.35" x2="8.35" y2="2.65" layer="51"/>
<smd name="69" x="7.75" y="3" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="2.85" x2="8.35" y2="3.15" layer="51"/>
<smd name="70" x="7.75" y="3.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="3.35" x2="8.35" y2="3.65" layer="51"/>
<smd name="71" x="7.75" y="4" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="3.85" x2="8.35" y2="4.15" layer="51"/>
<smd name="72" x="7.75" y="4.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="4.35" x2="8.35" y2="4.65" layer="51"/>
<smd name="73" x="7.75" y="5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="4.85" x2="8.35" y2="5.15" layer="51"/>
<smd name="74" x="7.75" y="5.5" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="5.35" x2="8.35" y2="5.65" layer="51"/>
<smd name="75" x="7.75" y="6" dx="1.2" dy="0.3" layer="1"/>
<rectangle x1="7" y1="5.85" x2="8.35" y2="6.15" layer="51"/>
<smd name="76" x="6" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="5.85" y1="7" x2="6.15" y2="8.35" layer="51"/>
<smd name="77" x="5.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="5.35" y1="7" x2="5.65" y2="8.35" layer="51"/>
<smd name="78" x="5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="4.85" y1="7" x2="5.15" y2="8.35" layer="51"/>
<smd name="79" x="4.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="4.35" y1="7" x2="4.65" y2="8.35" layer="51"/>
<smd name="80" x="4" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="3.85" y1="7" x2="4.15" y2="8.35" layer="51"/>
<smd name="81" x="3.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="3.35" y1="7" x2="3.65" y2="8.35" layer="51"/>
<smd name="82" x="3" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="2.85" y1="7" x2="3.15" y2="8.35" layer="51"/>
<smd name="83" x="2.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="2.35" y1="7" x2="2.65" y2="8.35" layer="51"/>
<smd name="84" x="2" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="1.85" y1="7" x2="2.15" y2="8.35" layer="51"/>
<smd name="85" x="1.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="1.35" y1="7" x2="1.65" y2="8.35" layer="51"/>
<smd name="86" x="1" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="0.85" y1="7" x2="1.15" y2="8.35" layer="51"/>
<smd name="87" x="0.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="0.35" y1="7" x2="0.65" y2="8.35" layer="51"/>
<smd name="88" x="0" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-0.15" y1="7" x2="0.15" y2="8.35" layer="51"/>
<smd name="89" x="-0.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-0.65" y1="7" x2="-0.35" y2="8.35" layer="51"/>
<smd name="90" x="-1" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-1.15" y1="7" x2="-0.85" y2="8.35" layer="51"/>
<smd name="91" x="-1.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-1.65" y1="7" x2="-1.35" y2="8.35" layer="51"/>
<smd name="92" x="-2" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-2.15" y1="7" x2="-1.85" y2="8.35" layer="51"/>
<smd name="93" x="-2.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-2.65" y1="7" x2="-2.35" y2="8.35" layer="51"/>
<smd name="94" x="-3" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-3.15" y1="7" x2="-2.85" y2="8.35" layer="51"/>
<smd name="95" x="-3.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-3.65" y1="7" x2="-3.35" y2="8.35" layer="51"/>
<smd name="96" x="-4" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-4.15" y1="7" x2="-3.85" y2="8.35" layer="51"/>
<smd name="97" x="-4.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-4.65" y1="7" x2="-4.35" y2="8.35" layer="51"/>
<smd name="98" x="-5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-5.15" y1="7" x2="-4.85" y2="8.35" layer="51"/>
<smd name="99" x="-5.5" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-5.65" y1="7" x2="-5.35" y2="8.35" layer="51"/>
<smd name="100" x="-6" y="7.75" dx="0.3" dy="1.2" layer="1"/>
<rectangle x1="-6.15" y1="7" x2="-5.85" y2="8.35" layer="51"/>
<text x="-8.35" y="8.985" size="1.27" layer="25">&gt;NAME</text>
<text x="-8.35" y="-10.255" size="1.27" layer="27">&gt;VALUE</text>
<circle x="-8.9" y="6.5" radius="0.2" width="0.3" layer="21"/>
<wire x1="-8.7" y1="1.5" x2="-9.4" y2="1.5" width="0.3" layer="21"/>
<wire x1="-8.7" y1="4" x2="-9" y2="4" width="0.3" layer="21"/>
<wire x1="-8.7" y1="-3.5" x2="-9.4" y2="-3.5" width="0.3" layer="21"/>
<wire x1="-8.7" y1="-1" x2="-9" y2="-1" width="0.3" layer="21"/>
<wire x1="-8.7" y1="-6" x2="-9" y2="-6" width="0.3" layer="21"/>
<wire x1="-4" y1="-8.7" x2="-4" y2="-9.4" width="0.3" layer="21"/>
<wire x1="1" y1="-8.7" x2="1" y2="-9.4" width="0.3" layer="21"/>
<wire x1="-1.5" y1="-8.7" x2="-1.5" y2="-9" width="0.3" layer="21"/>
<wire x1="3.5" y1="-8.7" x2="3.5" y2="-9" width="0.3" layer="21"/>
<wire x1="6" y1="-8.7" x2="6" y2="-9.4" width="0.3" layer="21"/>
<wire x1="8.7" y1="-1.5" x2="9.4" y2="-1.5" width="0.3" layer="21"/>
<wire x1="8.7" y1="-4" x2="9" y2="-4" width="0.3" layer="21"/>
<wire x1="8.7" y1="3.5" x2="9.4" y2="3.5" width="0.3" layer="21"/>
<wire x1="8.7" y1="1" x2="9" y2="1" width="0.3" layer="21"/>
<wire x1="8.7" y1="6" x2="9" y2="6" width="0.3" layer="21"/>
<wire x1="4" y1="8.7" x2="4" y2="9.4" width="0.3" layer="21"/>
<wire x1="-1" y1="8.7" x2="-1" y2="9.4" width="0.3" layer="21"/>
<wire x1="1.5" y1="8.7" x2="1.5" y2="9" width="0.3" layer="21"/>
<wire x1="-3.5" y1="8.7" x2="-3.5" y2="9" width="0.3" layer="21"/>
<wire x1="-6" y1="8.7" x2="-6" y2="9.4" width="0.3" layer="21"/>
</package>
<package name="1X05/90_FLAT">
<smd name="1" x="0" y="0" dx="3.3" dy="1.65" layer="1" roundness="100" rot="R90"/>
<smd name="2" x="2.54" y="0" dx="3.3" dy="1.65" layer="1" roundness="100" rot="R90"/>
<smd name="3" x="5.08" y="0" dx="3.3" dy="1.65" layer="1" roundness="100" rot="R90"/>
<text x="-1.905" y="0" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="13.335" y="0" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<smd name="4" x="7.62" y="0" dx="3.3" dy="1.65" layer="1" roundness="100" rot="R90"/>
<smd name="5" x="10.16" y="0" dx="3.3" dy="1.65" layer="1" roundness="100" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="CS43L22">
<pin name="SDA" x="-40.64" y="0" length="short"/>
<pin name="SCL" x="-40.64" y="-2.54" length="short" direction="in"/>
<pin name="AD0" x="-40.64" y="-5.08" length="short" direction="in"/>
<pin name="MCLK" x="-40.64" y="-10.16" length="short" direction="in"/>
<pin name="SCLK" x="-40.64" y="-12.7" length="short"/>
<pin name="SDIN" x="-40.64" y="-15.24" length="short" direction="in"/>
<pin name="LRCK" x="-40.64" y="-17.78" length="short"/>
<pin name="#RESET" x="-40.64" y="-20.32" length="short" direction="in"/>
<pin name="-VHPFILT" x="-40.64" y="-22.86" length="short" direction="out"/>
<pin name="FLYN" x="-40.64" y="-25.4" length="short" direction="out"/>
<pin name="FLYP" x="-40.64" y="-38.1" length="short" direction="out"/>
<pin name="+VHP" x="-40.64" y="-43.18" length="short" direction="in"/>
<pin name="VA" x="-40.64" y="-45.72" length="short" direction="pwr"/>
<pin name="VD" x="-40.64" y="-48.26" length="short" direction="pwr"/>
<pin name="TSTO" x="-40.64" y="-53.34" length="short" direction="nc"/>
<pin name="TSTO@1" x="-40.64" y="-55.88" length="short" direction="nc"/>
<pin name="VL" x="-40.64" y="-58.42" length="short" direction="pwr"/>
<pin name="DGND" x="-40.64" y="-60.96" length="short" direction="pwr"/>
<pin name="HP/LINE_OUTA" x="0" y="0" length="short" direction="out" rot="R180"/>
<pin name="HP/LINE_OUTB" x="0" y="-2.54" length="short" direction="out" rot="R180"/>
<pin name="SPKR/HP" x="0" y="-5.08" length="short" direction="in" rot="R180"/>
<pin name="SPKR_OUTA+" x="0" y="-20.32" length="short" direction="out" rot="R180"/>
<pin name="SPKR_OUTA-" x="0" y="-17.78" length="short" direction="out" rot="R180"/>
<pin name="SPKR_OUTB+" x="0" y="-15.24" length="short" direction="out" rot="R180"/>
<pin name="SPKR_OUTB-" x="0" y="-12.7" length="short" direction="out" rot="R180"/>
<pin name="VP" x="0" y="-22.86" length="short" direction="in" rot="R180"/>
<pin name="VP@1" x="0" y="-25.4" length="short" direction="in" rot="R180"/>
<pin name="AIN1B" x="0" y="-48.26" length="short" direction="in" rot="R180"/>
<pin name="AIN1A" x="0" y="-45.72" length="short" direction="in" rot="R180"/>
<pin name="AIN2B" x="0" y="-43.18" length="short" direction="in" rot="R180"/>
<pin name="AIN2A" x="0" y="-40.64" length="short" direction="in" rot="R180"/>
<pin name="AIN3B" x="0" y="-38.1" length="short" direction="in" rot="R180"/>
<pin name="AIN3A" x="0" y="-35.56" length="short" direction="in" rot="R180"/>
<pin name="AIN4B" x="0" y="-33.02" length="short" direction="in" rot="R180"/>
<pin name="AIN4A" x="0" y="-30.48" length="short" direction="in" rot="R180"/>
<pin name="VQ" x="0" y="-53.34" length="short" direction="out" rot="R180"/>
<pin name="AFILTB" x="0" y="-55.88" length="short" direction="out" rot="R180"/>
<pin name="AFILTA" x="0" y="-58.42" length="short" direction="out" rot="R180"/>
<pin name="FILT+" x="0" y="-60.96" length="short" direction="out" rot="R180"/>
<pin name="AGND" x="0" y="-63.5" length="short" direction="pwr" rot="R180"/>
<wire x1="-38.1" y1="-66.04" x2="-2.54" y2="-66.04" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-66.04" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-38.1" y2="2.54" width="0.254" layer="94"/>
<wire x1="-38.1" y1="2.54" x2="-38.1" y2="-66.04" width="0.254" layer="94"/>
<text x="-20.32" y="5.08" size="1.778" layer="95" align="center">&gt;NAME</text>
<text x="-20.32" y="-68.58" size="1.778" layer="96" align="center">&gt;VALUE</text>
<pin name="GND/PAD" x="-40.64" y="-63.5" visible="pin" length="short" direction="pwr"/>
</symbol>
<symbol name="NOKIA1100_KEY_PAD">
<pin name="OUTER" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="INNER" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="0" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" align="center">&gt;NAME</text>
</symbol>
<symbol name="NOKIA1100_DISP">
<pin name="#RES" x="2.54" y="-7.62" length="short" direction="in" rot="R180"/>
<pin name="#CS" x="2.54" y="0" length="short" direction="in" rot="R180"/>
<pin name="SCLK" x="2.54" y="-5.08" length="short" direction="in" rot="R180"/>
<pin name="VDD1" x="2.54" y="-10.16" length="short" direction="pwr" rot="R180"/>
<pin name="VDD2" x="2.54" y="-12.7" length="short" direction="pwr" rot="R180"/>
<pin name="VSS" x="2.54" y="-17.78" length="short" direction="pwr" rot="R180"/>
<pin name="BKL" x="2.54" y="-15.24" length="short" direction="in" rot="R180"/>
<pin name="SDIN" x="2.54" y="-2.54" length="short" direction="in" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-20.32" width="0.254" layer="94"/>
<wire x1="0" y1="-20.32" x2="-12.7" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-20.32" x2="-12.7" y2="2.54" width="0.254" layer="94"/>
<wire x1="-12.7" y1="2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="-7.62" y="5.08" size="1.778" layer="95" align="center">&gt;NAME</text>
<text x="0" y="-22.86" size="1.778" layer="96" align="top-right">Nokia 1100
Display</text>
</symbol>
<symbol name="NOKIA1100_VIBRATOR">
<circle x="0" y="-3.81" radius="2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-1.524" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-6.096" x2="-1.27" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-7.62" x2="1.27" y2="-7.62" width="0.254" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="1.27" y2="-6.096" width="0.254" layer="94"/>
<wire x1="-0.762" y1="-4.572" x2="-0.762" y2="-2.794" width="0.254" layer="94"/>
<wire x1="-0.762" y1="-2.794" x2="0" y2="-3.81" width="0.254" layer="94"/>
<wire x1="0" y1="-3.81" x2="0.762" y2="-2.794" width="0.254" layer="94"/>
<wire x1="0.762" y1="-2.794" x2="0.762" y2="-4.572" width="0.254" layer="94"/>
<pin name="P$1" x="0" y="2.54" visible="off" length="short" rot="R270"/>
<pin name="P$2" x="0" y="-10.16" visible="off" length="short" rot="R90"/>
<text x="2.54" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-7.62" size="1.778" layer="96" align="top-left">Vibrator</text>
</symbol>
<symbol name="NOKIA1100_BATTERY_CONN">
<pin name="+" x="0" y="0" visible="pin" length="short" direction="out" rot="R180"/>
<pin name="SRV" x="0" y="-2.54" visible="pin" length="short" direction="nc" rot="R180"/>
<pin name="-" x="0" y="-5.08" visible="pin" length="short" direction="out" rot="R180"/>
<text x="-2.54" y="5.08" size="1.778" layer="95" align="top-right">&gt;NAME</text>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-7.62" x2="-10.16" y2="2.54" width="0.254" layer="94"/>
<wire x1="-10.16" y1="2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<text x="-2.54" y="-10.16" size="1.778" layer="96" align="bottom-right">LiIon</text>
</symbol>
<symbol name="NOKIA1100_EXT_CONN">
<pin name="A" x="0" y="0" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="B" x="0" y="-2.54" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="AGND" x="0" y="-5.08" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="BTN" x="0" y="-10.16" visible="pin" length="short" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-12.7" x2="-12.7" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-12.7" x2="-12.7" y2="2.54" width="0.254" layer="94"/>
<wire x1="-12.7" y1="2.54" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<text x="-2.54" y="5.08" size="1.778" layer="95" align="top-right">&gt;NAME</text>
<text x="-2.54" y="-17.78" size="1.778" layer="95" align="bottom-right">External
Connector</text>
</symbol>
<symbol name="+2V5">
<text x="0" y="2.54" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<pin name="+2V5" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
<circle x="0" y="0.762" radius="0.762" width="0.254" layer="94"/>
</symbol>
<symbol name="+3V3">
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
<text x="0" y="2.54" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<circle x="0" y="0.762" radius="0.762" width="0.254" layer="94"/>
</symbol>
<symbol name="MFPS">
<wire x1="-1.016" y1="-2.54" x2="-1.016" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.016" y1="2.54" x2="-2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.905" x2="0.5334" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="0.508" y1="1.905" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="5.08" y1="1.905" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="2.2352" y1="0" x2="2.286" y2="0" width="0.1524" layer="94"/>
<wire x1="2.286" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="2.286" y1="0" x2="1.016" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-0.508" x2="1.016" y2="0.508" width="0.1524" layer="94"/>
<wire x1="1.016" y1="0.508" x2="2.286" y2="0" width="0.1524" layer="94"/>
<wire x1="1.143" y1="0" x2="0.254" y2="0" width="0.1524" layer="94"/>
<wire x1="1.143" y1="0.254" x2="2.032" y2="0" width="0.3048" layer="94"/>
<wire x1="2.032" y1="0" x2="1.143" y2="-0.254" width="0.3048" layer="94"/>
<wire x1="1.143" y1="-0.254" x2="1.143" y2="0" width="0.3048" layer="94"/>
<wire x1="1.143" y1="0" x2="1.397" y2="0" width="0.3048" layer="94"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.08" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.715" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="5.715" y1="-0.635" x2="4.445" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="4.445" y1="-0.635" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.715" y1="0.762" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="4.445" y2="0.762" width="0.1524" layer="94"/>
<wire x1="4.445" y1="0.762" x2="4.191" y2="1.016" width="0.1524" layer="94"/>
<wire x1="5.715" y1="0.762" x2="5.969" y2="0.508" width="0.1524" layer="94"/>
<circle x="2.54" y="1.905" radius="0.127" width="0.4064" layer="94"/>
<circle x="2.54" y="-1.905" radius="0.127" width="0.4064" layer="94"/>
<text x="7.62" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="7.62" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="1.524" y="-3.302" size="0.8128" layer="93">D</text>
<text x="1.524" y="2.54" size="0.8128" layer="93">S</text>
<text x="-2.286" y="1.27" size="0.8128" layer="93">G</text>
<rectangle x1="-0.254" y1="1.27" x2="0.508" y2="2.54" layer="94"/>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="-1.27" layer="94"/>
<rectangle x1="-0.254" y1="-0.889" x2="0.508" y2="0.889" layer="94"/>
<pin name="G" x="-2.54" y="2.54" visible="off" length="point" direction="pas"/>
<pin name="D" x="2.54" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="S" x="2.54" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
</symbol>
<symbol name="MFNS">
<wire x1="-3.556" y1="-2.54" x2="-3.556" y2="2.54" width="0.254" layer="94"/>
<wire x1="-3.556" y1="2.54" x2="-5.08" y2="2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1.905" x2="-2.0066" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="1.905" x2="0" y2="1.905" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="1.905" x2="0" y2="1.905" width="0.1524" layer="94"/>
<wire x1="0" y1="1.905" x2="0" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-1.9812" y1="0" x2="-2.032" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="0" x2="-2.286" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="0" x2="-0.762" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="-0.508" x2="-0.762" y2="0.508" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="0.508" x2="-2.032" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="0" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="0.254" x2="-1.778" y2="0" width="0.3048" layer="94"/>
<wire x1="-1.778" y1="0" x2="-0.889" y2="-0.254" width="0.3048" layer="94"/>
<wire x1="-0.889" y1="-0.254" x2="-0.889" y2="0" width="0.3048" layer="94"/>
<wire x1="-0.889" y1="0" x2="-1.143" y2="0" width="0.3048" layer="94"/>
<circle x="0" y="1.905" radius="0.127" width="0.4064" layer="94"/>
<circle x="0" y="-1.905" radius="0.127" width="0.4064" layer="94"/>
<text x="5.08" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="5.08" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.016" y="-3.302" size="0.8128" layer="93">D</text>
<text x="-1.016" y="2.54" size="0.8128" layer="93">S</text>
<text x="-4.826" y="1.27" size="0.8128" layer="93">G</text>
<rectangle x1="-2.794" y1="1.27" x2="-2.032" y2="2.54" layer="94"/>
<rectangle x1="-2.794" y1="-2.54" x2="-2.032" y2="-1.27" layer="94"/>
<rectangle x1="-2.794" y1="-0.889" x2="-2.032" y2="0.889" layer="94" rot="R180"/>
<pin name="G" x="-5.08" y="2.54" visible="off" length="point" direction="pas"/>
<pin name="D" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="S" x="0" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
<wire x1="0" y1="1.905" x2="0" y2="0" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="-0.762" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-0.762" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-0.762" x2="1.905" y2="0.635" width="0.1524" layer="94"/>
<wire x1="1.905" y1="0.635" x2="3.175" y2="0.635" width="0.1524" layer="94"/>
<wire x1="3.175" y1="0.635" x2="2.54" y2="-0.762" width="0.1524" layer="94"/>
<wire x1="1.905" y1="-0.762" x2="2.54" y2="-0.762" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-0.762" x2="3.175" y2="-0.762" width="0.1524" layer="94"/>
<wire x1="3.175" y1="-0.762" x2="3.429" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.905" y1="-0.762" x2="1.651" y2="-0.508" width="0.1524" layer="94"/>
</symbol>
<symbol name="+5V">
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
<text x="0" y="2.54" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<circle x="0" y="0.762" radius="0.762" width="0.254" layer="94"/>
</symbol>
<symbol name="VBAT">
<pin name="VBAT" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
<text x="0" y="2.54" size="1.778" layer="96" align="bottom-center">&gt;VALUE</text>
<circle x="0" y="0.762" radius="0.762" width="0.254" layer="94"/>
</symbol>
<symbol name="USBLC6-2">
<pin name="IO1.2" x="5.08" y="0" length="middle" direction="pas" rot="R180"/>
<pin name="VBUS" x="5.08" y="-2.54" length="middle" direction="pas" rot="R180"/>
<pin name="IO2.2" x="5.08" y="-5.08" length="middle" direction="pas" rot="R180"/>
<pin name="IO2.1" x="-22.86" y="-5.08" length="middle" direction="pas"/>
<pin name="GND" x="-22.86" y="-2.54" length="middle" direction="pas"/>
<pin name="IO1.1" x="-22.86" y="0" length="middle" direction="pas"/>
<wire x1="-17.78" y1="2.54" x2="-17.78" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-7.62" x2="0" y2="-7.62" width="0.254" layer="94"/>
<wire x1="0" y1="-7.62" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-17.78" y2="2.54" width="0.254" layer="94"/>
<text x="-17.78" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="-17.78" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MICROSD_CONN">
<pin name="VDD" x="2.54" y="0" visible="pin" length="short" direction="pwr" rot="R180"/>
<pin name="D2" x="2.54" y="-2.54" visible="pin" length="short" rot="R180"/>
<pin name="D3" x="2.54" y="-5.08" visible="pin" length="short" rot="R180"/>
<pin name="CMD" x="2.54" y="-7.62" visible="pin" length="short" rot="R180"/>
<pin name="CK" x="2.54" y="-10.16" visible="pin" length="short" direction="in" rot="R180"/>
<pin name="D0" x="2.54" y="-12.7" visible="pin" length="short" rot="R180"/>
<pin name="D1" x="2.54" y="-15.24" visible="pin" length="short" rot="R180"/>
<pin name="VSS" x="2.54" y="-17.78" visible="pin" length="short" direction="pwr" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-30.48" width="0.254" layer="94"/>
<wire x1="0" y1="-30.48" x2="-12.7" y2="-30.48" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-30.48" x2="-12.7" y2="2.54" width="0.254" layer="94"/>
<wire x1="-12.7" y1="2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="-12.7" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<pin name="SNS1" x="2.54" y="-22.86" visible="off" length="short" direction="pas" rot="R180"/>
<pin name="SNS2" x="2.54" y="-25.4" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="-2.54" y1="-22.86" x2="-5.08" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-21.59" x2="-7.62" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-22.86" x2="-10.16" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-25.4" x2="-7.62" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-25.4" x2="-5.08" y2="-24.13" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-25.4" x2="-2.54" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-22.86" x2="-10.16" y2="-27.94" width="0.254" layer="94"/>
<circle x="-10.16" y="-25.4" radius="0.254" width="0.508" layer="94"/>
<pin name="SH" x="2.54" y="-27.94" visible="pin" length="short" direction="pwr" rot="R180"/>
<wire x1="-7.62" y1="-27.94" x2="-10.16" y2="-27.94" width="0.254" layer="94"/>
</symbol>
<symbol name="R-EU">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="C-EU">
<wire x1="0" y1="0" x2="0" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-2.032" width="0.1524" layer="94"/>
<text x="1.524" y="0.381" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-4.699" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="-2.032" x2="2.032" y2="-1.524" layer="94"/>
<rectangle x1="-2.032" y1="-1.016" x2="2.032" y2="-0.508" layer="94"/>
<pin name="1" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="LTC4054ES5">
<pin name="VCC" x="-2.54" y="0" length="short" direction="pwr"/>
<pin name="GND" x="-2.54" y="-5.08" length="short" direction="pwr"/>
<pin name="PROG" x="20.32" y="-5.08" length="short" direction="in" rot="R180"/>
<pin name="#CHRG" x="20.32" y="-2.54" length="short" direction="out" rot="R180"/>
<pin name="BAT" x="20.32" y="0" length="short" direction="out" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-7.62" width="0.254" layer="94"/>
<wire x1="0" y1="-7.62" x2="17.78" y2="-7.62" width="0.254" layer="94"/>
<wire x1="17.78" y1="-7.62" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" font="vector" align="top-left">&gt;NAME</text>
<text x="0" y="-10.16" size="1.778" layer="96" font="vector" rot="MR180" align="top-left">&gt;VALUE</text>
</symbol>
<symbol name="D">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="NPN">
<wire x1="2.54" y1="2.54" x2="0.508" y2="1.524" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-1.524" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.778" y2="-1.524" width="0.1524" layer="94"/>
<wire x1="1.54" y1="-2.04" x2="0.308" y2="-1.424" width="0.1524" layer="94"/>
<wire x1="1.524" y1="-2.413" x2="2.286" y2="-2.413" width="0.254" layer="94"/>
<wire x1="2.286" y1="-2.413" x2="1.778" y2="-1.778" width="0.254" layer="94"/>
<wire x1="1.778" y1="-1.778" x2="1.524" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.524" y1="-2.286" x2="1.905" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.905" y1="-2.286" x2="1.778" y2="-2.032" width="0.254" layer="94"/>
<text x="-10.16" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="5.08" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="2.54" layer="94"/>
<pin name="B" x="-2.54" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="E" x="2.54" y="-5.08" visible="off" length="short" direction="pas" swaplevel="3" rot="R90"/>
<pin name="C" x="2.54" y="5.08" visible="off" length="short" direction="pas" swaplevel="2" rot="R270"/>
</symbol>
<symbol name="VT_NPN_DIGITAL">
<wire x1="2.54" y1="2.54" x2="0.508" y2="1.524" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-1.524" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.778" y2="-1.524" width="0.1524" layer="94"/>
<wire x1="1.54" y1="-2.04" x2="0.308" y2="-1.424" width="0.1524" layer="94"/>
<wire x1="1.524" y1="-2.413" x2="2.286" y2="-2.413" width="0.254" layer="94"/>
<wire x1="2.286" y1="-2.413" x2="1.778" y2="-1.778" width="0.254" layer="94"/>
<wire x1="1.778" y1="-1.778" x2="1.524" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.524" y1="-2.286" x2="1.905" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.905" y1="-2.286" x2="1.778" y2="-2.032" width="0.254" layer="94"/>
<text x="-10.16" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="5.08" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="2.54" layer="94"/>
<pin name="B" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
<pin name="E" x="2.54" y="-5.08" visible="off" length="short" direction="pas" swaplevel="3" rot="R90"/>
<pin name="C" x="2.54" y="5.08" visible="off" length="short" direction="pas" swaplevel="2" rot="R270"/>
<wire x1="0" y1="0" x2="-0.762" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="0" x2="-0.762" y2="0.508" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="0.508" x2="-2.032" y2="0.508" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="0.508" x2="-2.032" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="0" x2="-2.032" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="-0.508" x2="-0.762" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="-0.762" y1="-0.508" x2="-0.762" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.032" y2="0" width="0.1524" layer="94"/>
</symbol>
<symbol name="ESDA6V1W5">
<pin name="P$1" x="-5.08" y="5.08" visible="pad" length="short" direction="pas"/>
<pin name="P$2" x="-5.08" y="0" visible="pad" length="short" direction="pas"/>
<pin name="P$3" x="-5.08" y="-5.08" visible="pad" length="short" direction="pas"/>
<pin name="P$4" x="15.24" y="-5.08" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="P$5" x="15.24" y="5.08" visible="pad" length="short" direction="pas" rot="R180"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="10.16" y2="5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="5.08" y2="0" width="0.1524" layer="94"/>
<wire x1="0" y1="-5.08" x2="10.16" y2="-5.08" width="0.1524" layer="94"/>
<circle x="5.08" y="-5.08" radius="0.254" width="0.508" layer="94"/>
<wire x1="7.62" y1="-3.556" x2="7.62" y2="-6.604" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-6.604" x2="10.16" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="7.62" y2="-3.556" width="0.1524" layer="94"/>
<wire x1="9.652" y1="-3.048" x2="10.16" y2="-3.556" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-3.556" x2="10.16" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="10.16" y2="-6.604" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-6.604" x2="10.668" y2="-7.112" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-6.604" x2="2.54" y2="-3.556" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-3.556" x2="0" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="-5.08" x2="2.54" y2="-6.604" width="0.1524" layer="94"/>
<wire x1="0.508" y1="-7.112" x2="0" y2="-6.604" width="0.1524" layer="94"/>
<wire x1="0" y1="-6.604" x2="0" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="-5.08" x2="0" y2="-3.556" width="0.1524" layer="94"/>
<wire x1="0" y1="-3.556" x2="-0.508" y2="-3.048" width="0.1524" layer="94"/>
<wire x1="7.62" y1="6.604" x2="7.62" y2="3.556" width="0.1524" layer="94"/>
<wire x1="7.62" y1="3.556" x2="10.16" y2="5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="5.08" x2="7.62" y2="6.604" width="0.1524" layer="94"/>
<wire x1="9.652" y1="7.112" x2="10.16" y2="6.604" width="0.1524" layer="94"/>
<wire x1="10.16" y1="6.604" x2="10.16" y2="5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="5.08" x2="10.16" y2="3.556" width="0.1524" layer="94"/>
<wire x1="10.16" y1="3.556" x2="10.668" y2="3.048" width="0.1524" layer="94"/>
<wire x1="2.54" y1="3.556" x2="2.54" y2="6.604" width="0.1524" layer="94"/>
<wire x1="2.54" y1="6.604" x2="0" y2="5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="2.54" y2="3.556" width="0.1524" layer="94"/>
<wire x1="0.508" y1="3.048" x2="0" y2="3.556" width="0.1524" layer="94"/>
<wire x1="0" y1="3.556" x2="0" y2="5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="6.604" width="0.1524" layer="94"/>
<wire x1="0" y1="6.604" x2="-0.508" y2="7.112" width="0.1524" layer="94"/>
<circle x="5.08" y="0" radius="0.254" width="0.508" layer="94"/>
<circle x="5.08" y="5.08" radius="0.254" width="0.508" layer="94"/>
<wire x1="-2.54" y1="8.89" x2="-2.54" y2="5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="-8.89" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-8.89" x2="12.7" y2="-8.89" width="0.1524" layer="94"/>
<wire x1="12.7" y1="-8.89" x2="12.7" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="12.7" y1="-5.08" x2="12.7" y2="5.08" width="0.1524" layer="94"/>
<wire x1="12.7" y1="5.08" x2="12.7" y2="8.89" width="0.1524" layer="94"/>
<wire x1="12.7" y1="8.89" x2="-2.54" y2="8.89" width="0.1524" layer="94"/>
<text x="-2.54" y="10.16" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<wire x1="12.7" y1="5.08" x2="10.16" y2="5.08" width="0.1524" layer="94"/>
<wire x1="10.16" y1="-5.08" x2="12.7" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="-5.08" x2="-2.54" y2="-5.08" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="-2.54" y2="5.08" width="0.1524" layer="94"/>
</symbol>
<symbol name="USB3300">
<pin name="GND" x="0" y="-50.8" length="short" direction="pwr"/>
<pin name="GND@1" x="0" y="-53.34" length="short" direction="pwr"/>
<pin name="CPEN" x="0" y="-38.1" length="short" direction="out"/>
<pin name="VBUS" x="0" y="0" length="short"/>
<pin name="ID" x="0" y="-35.56" length="short" direction="in"/>
<pin name="VDD3_3" x="0" y="-12.7" length="short" direction="pwr"/>
<pin name="DP" x="0" y="-33.02" length="short"/>
<pin name="DM" x="0" y="-30.48" length="short"/>
<pin name="RESET" x="35.56" y="-30.48" length="short" direction="in" rot="R180"/>
<pin name="EXTVBUS" x="0" y="-40.64" length="short" direction="in"/>
<pin name="NXT" x="35.56" y="-22.86" length="short" direction="out" rot="R180"/>
<pin name="DIR" x="35.56" y="-25.4" length="short" direction="out" rot="R180"/>
<pin name="STP" x="35.56" y="-20.32" length="short" direction="in" rot="R180"/>
<pin name="CLKOUT" x="35.56" y="-27.94" length="short" direction="out" rot="R180"/>
<pin name="VDD1_8" x="35.56" y="-48.26" length="short" direction="out" rot="R180"/>
<pin name="VDD3_3@1" x="0" y="-15.24" length="short" direction="pwr"/>
<pin name="DATA7" x="35.56" y="-17.78" length="short" rot="R180"/>
<pin name="DATA6" x="35.56" y="-15.24" length="short" rot="R180"/>
<pin name="DATA5" x="35.56" y="-12.7" length="short" rot="R180"/>
<pin name="DATA4" x="35.56" y="-10.16" length="short" rot="R180"/>
<pin name="DATA3" x="35.56" y="-7.62" length="short" rot="R180"/>
<pin name="DATA2" x="35.56" y="-5.08" length="short" rot="R180"/>
<pin name="DATA1" x="35.56" y="-2.54" length="short" rot="R180"/>
<pin name="DATA0" x="35.56" y="0" length="short" rot="R180"/>
<pin name="VDD3_3@2" x="0" y="-17.78" length="short" direction="pwr"/>
<pin name="VDD1_8@1" x="35.56" y="-50.8" length="short" direction="out" rot="R180"/>
<pin name="XO" x="35.56" y="-35.56" length="short" direction="out" rot="R180"/>
<pin name="XI" x="35.56" y="-43.18" length="short" direction="in" rot="R180"/>
<pin name="VDDA1_8" x="35.56" y="-53.34" length="short" direction="out" rot="R180"/>
<pin name="VDD3_3@3" x="0" y="-20.32" length="short" direction="pwr"/>
<pin name="REG_EN" x="0" y="-10.16" length="short"/>
<pin name="RBIAS" x="35.56" y="-55.88" length="short" direction="in" rot="R180"/>
<wire x1="2.54" y1="-58.42" x2="33.02" y2="-58.42" width="0.254" layer="94"/>
<wire x1="33.02" y1="-58.42" x2="33.02" y2="2.54" width="0.254" layer="94"/>
<wire x1="33.02" y1="2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="-58.42" width="0.254" layer="94"/>
<text x="2.54" y="3.81" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-60.96" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND_FLAG" x="0" y="-55.88" visible="pin" length="short" direction="pwr"/>
</symbol>
<symbol name="USB_MINI_CONN">
<pin name="VDD" x="2.54" y="0" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="DM" x="2.54" y="-2.54" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="DP" x="2.54" y="-5.08" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="SC" x="2.54" y="-7.62" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="GND" x="2.54" y="-10.16" visible="pin" length="short" direction="pas" rot="R180"/>
<pin name="SH" x="2.54" y="-12.7" visible="pin" length="short" direction="pas" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-15.24" width="0.254" layer="94"/>
<wire x1="0" y1="-15.24" x2="-10.16" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-15.24" x2="-10.16" y2="2.54" width="0.254" layer="94"/>
<wire x1="-10.16" y1="2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="-10.16" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="0" y="-17.78" size="1.778" layer="95" align="bottom-right">&gt;VALUE</text>
</symbol>
<symbol name="QUARTZ_5MM">
<pin name="P$1" x="0" y="5.08" visible="off" length="point" direction="pas" rot="R270"/>
<pin name="P$2" x="0" y="-2.54" visible="off" length="point" direction="pas" rot="R90"/>
<wire x1="-1.524" y1="2.794" x2="0" y2="2.794" width="0.1524" layer="94"/>
<wire x1="0" y1="2.794" x2="1.524" y2="2.794" width="0.1524" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="2.794" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="2.032" x2="2.54" y2="2.032" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.032" x2="2.54" y2="0.508" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-0.254" x2="0" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="0" y1="-0.254" x2="1.524" y2="-0.254" width="0.1524" layer="94"/>
<wire x1="0" y1="-0.254" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="2.032" x2="-2.54" y2="0.508" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0.508" x2="2.54" y2="0.508" width="0.1524" layer="94"/>
<text x="3.81" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="3.81" y="0" size="1.778" layer="96" rot="MR180">&gt;VALUE</text>
</symbol>
<symbol name="LIS302DL">
<pin name="VDD_IO" x="-2.54" y="-2.54" length="short" direction="pwr"/>
<pin name="VDD" x="-2.54" y="-5.08" length="short" direction="pwr"/>
<pin name="RESERVED" x="-2.54" y="-7.62" length="short" direction="nc"/>
<pin name="SDA_SDI_SDO" x="-2.54" y="-10.16" length="short"/>
<pin name="SCL_SPC" x="-2.54" y="-12.7" length="short"/>
<pin name="INT1" x="-2.54" y="-15.24" length="short" direction="out"/>
<pin name="INT2" x="-2.54" y="-17.78" length="short" direction="out"/>
<pin name="RESERVED@1" x="35.56" y="-17.78" length="short" direction="nc" rot="R180"/>
<pin name="GND" x="35.56" y="-15.24" length="short" direction="pwr" rot="R180"/>
<pin name="GND@1" x="35.56" y="-12.7" length="short" direction="pwr" rot="R180"/>
<pin name="GND@2" x="35.56" y="-10.16" length="short" direction="pwr" rot="R180"/>
<pin name="GND@3" x="35.56" y="-7.62" length="short" direction="pwr" rot="R180"/>
<pin name="SDO" x="35.56" y="-5.08" length="short" rot="R180"/>
<pin name="CS.I2C_SPI" x="35.56" y="-2.54" length="short" rot="R180"/>
<wire x1="0" y1="-20.32" x2="33.02" y2="-20.32" width="0.254" layer="94"/>
<wire x1="33.02" y1="-20.32" x2="33.02" y2="0" width="0.254" layer="94"/>
<wire x1="33.02" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-20.32" width="0.254" layer="94"/>
<text x="0" y="1.27" size="1.778" layer="95">&gt;NAME</text>
<text x="0" y="-22.86" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="LD3985MXXR">
<pin name="VIN" x="-2.54" y="0" length="short"/>
<pin name="INH" x="-2.54" y="-2.54" length="short"/>
<pin name="GND" x="-2.54" y="-5.08" length="short"/>
<pin name="BYPASS" x="22.86" y="-5.08" length="short" rot="R180"/>
<pin name="VOUT" x="22.86" y="0" length="short" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-7.62" width="0.254" layer="94"/>
<wire x1="0" y1="-7.62" x2="20.32" y2="-7.62" width="0.254" layer="94"/>
<wire x1="20.32" y1="-7.62" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="0" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="STM32F4XXIXT">
<pin name="PE2" x="-205.74" y="-22.86" length="short"/>
<pin name="PE3" x="-205.74" y="-25.4" length="short"/>
<pin name="PE4" x="-205.74" y="-27.94" length="short"/>
<pin name="PE5" x="-205.74" y="-30.48" length="short"/>
<pin name="PE6" x="-205.74" y="-33.02" length="short"/>
<pin name="VBAT" x="-114.3" y="86.36" length="short" direction="pwr" rot="R180"/>
<pin name="PI8" x="-149.86" y="66.04" length="short"/>
<pin name="PC13" x="-205.74" y="5.08" length="short"/>
<pin name="PC14" x="-205.74" y="2.54" length="short"/>
<pin name="PC15" x="-205.74" y="0" length="short"/>
<pin name="PI9" x="-149.86" y="63.5" length="short"/>
<pin name="PI10" x="-149.86" y="60.96" length="short"/>
<pin name="PI11" x="-149.86" y="58.42" length="short"/>
<pin name="VSS" x="-149.86" y="48.26" length="short" direction="pwr"/>
<pin name="VDD" x="-114.3" y="83.82" length="short" direction="pwr" rot="R180"/>
<pin name="PF0" x="-180.34" y="-17.78" length="short" rot="R180"/>
<pin name="PF1" x="-180.34" y="-20.32" length="short" rot="R180"/>
<pin name="PF2" x="-180.34" y="-22.86" length="short" rot="R180"/>
<pin name="PF3" x="-180.34" y="-25.4" length="short" rot="R180"/>
<pin name="PF4" x="-180.34" y="-27.94" length="short" rot="R180"/>
<pin name="PF5" x="-180.34" y="-30.48" length="short" rot="R180"/>
<pin name="VSS@1" x="-149.86" y="45.72" length="short" direction="pwr"/>
<pin name="VDD@1" x="-114.3" y="81.28" length="short" direction="pwr" rot="R180"/>
<pin name="PF6" x="-180.34" y="-33.02" length="short" rot="R180"/>
<pin name="PF7" x="-180.34" y="-35.56" length="short" rot="R180"/>
<pin name="PF8" x="-180.34" y="-38.1" length="short" rot="R180"/>
<pin name="PF9" x="-180.34" y="-40.64" length="short" rot="R180"/>
<pin name="PF10" x="-180.34" y="-43.18" length="short" rot="R180"/>
<pin name="PH0" x="-180.34" y="-73.66" length="short" rot="R180"/>
<pin name="PH1" x="-180.34" y="-76.2" length="short" rot="R180"/>
<pin name="NRST" x="-114.3" y="35.56" length="short" direction="in" rot="R180"/>
<pin name="PC0" x="-205.74" y="38.1" length="short"/>
<pin name="PC1" x="-205.74" y="35.56" length="short"/>
<pin name="PC2" x="-205.74" y="33.02" length="short"/>
<pin name="PC3" x="-205.74" y="30.48" length="short"/>
<pin name="VDDA" x="-114.3" y="43.18" length="short" direction="pwr" rot="R180"/>
<pin name="VSSA" x="-149.86" y="20.32" length="short" direction="pwr"/>
<pin name="VREF+" x="-114.3" y="45.72" length="short" direction="in" rot="R180"/>
<pin name="VDDA@1" x="-114.3" y="40.64" length="short" direction="pwr" rot="R180"/>
<pin name="PA0" x="-205.74" y="93.98" length="short"/>
<pin name="PA1" x="-205.74" y="91.44" length="short"/>
<pin name="PA2" x="-205.74" y="88.9" length="short"/>
<pin name="PH2" x="-180.34" y="-78.74" length="short" rot="R180"/>
<pin name="PH3" x="-180.34" y="-81.28" length="short" rot="R180"/>
<pin name="PH4" x="-180.34" y="-83.82" length="short" rot="R180"/>
<pin name="PH5" x="-180.34" y="-86.36" length="short" rot="R180"/>
<pin name="PA3" x="-205.74" y="86.36" length="short"/>
<pin name="BYPASS_REG" x="-114.3" y="27.94" length="short" direction="in" rot="R180"/>
<pin name="VDD@2" x="-114.3" y="78.74" length="short" direction="pwr" rot="R180"/>
<pin name="PA4" x="-205.74" y="83.82" length="short"/>
<pin name="PA5" x="-205.74" y="81.28" length="short"/>
<pin name="PA6" x="-205.74" y="78.74" length="short"/>
<pin name="PA7" x="-205.74" y="76.2" length="short"/>
<pin name="PC4" x="-205.74" y="27.94" length="short"/>
<pin name="PC5" x="-205.74" y="25.4" length="short"/>
<pin name="PB0" x="-180.34" y="93.98" length="short" rot="R180"/>
<pin name="PB1" x="-180.34" y="91.44" length="short" rot="R180"/>
<pin name="PB2" x="-180.34" y="88.9" length="short" rot="R180"/>
<pin name="PF11" x="-180.34" y="-45.72" length="short" rot="R180"/>
<pin name="PF12" x="-180.34" y="-48.26" length="short" rot="R180"/>
<pin name="VSS@2" x="-149.86" y="43.18" length="short" direction="pwr"/>
<pin name="VDD@3" x="-114.3" y="76.2" length="short" direction="pwr" rot="R180"/>
<pin name="PF13" x="-180.34" y="-50.8" length="short" rot="R180"/>
<pin name="PF14" x="-180.34" y="-53.34" length="short" rot="R180"/>
<pin name="PF15" x="-180.34" y="-55.88" length="short" rot="R180"/>
<pin name="PG0" x="-205.74" y="-73.66" length="short"/>
<pin name="PG1" x="-205.74" y="-76.2" length="short"/>
<pin name="PE7" x="-205.74" y="-35.56" length="short"/>
<pin name="PE8" x="-205.74" y="-38.1" length="short"/>
<pin name="PE9" x="-205.74" y="-40.64" length="short"/>
<pin name="VSS@3" x="-149.86" y="40.64" length="short" direction="pwr"/>
<pin name="VDD@4" x="-114.3" y="73.66" length="short" direction="pwr" rot="R180"/>
<pin name="PE10" x="-205.74" y="-43.18" length="short"/>
<pin name="PE11" x="-205.74" y="-45.72" length="short"/>
<pin name="PE12" x="-205.74" y="-48.26" length="short"/>
<pin name="PE13" x="-205.74" y="-50.8" length="short"/>
<pin name="PE14" x="-205.74" y="-53.34" length="short"/>
<pin name="PE15" x="-205.74" y="-55.88" length="short"/>
<pin name="PB10" x="-180.34" y="68.58" length="short" rot="R180"/>
<pin name="PB11" x="-180.34" y="66.04" length="short" rot="R180"/>
<pin name="VCAP_1" x="-114.3" y="22.86" length="short" direction="out" rot="R180"/>
<pin name="VDD@5" x="-114.3" y="71.12" length="short" direction="pwr" rot="R180"/>
<pin name="PH6" x="-180.34" y="-88.9" length="short" rot="R180"/>
<pin name="PH7" x="-180.34" y="-91.44" length="short" rot="R180"/>
<pin name="PH8" x="-180.34" y="-93.98" length="short" rot="R180"/>
<pin name="PH9" x="-180.34" y="-96.52" length="short" rot="R180"/>
<pin name="PH10" x="-180.34" y="-99.06" length="short" rot="R180"/>
<pin name="PH11" x="-180.34" y="-101.6" length="short" rot="R180"/>
<pin name="PH12" x="-180.34" y="-104.14" length="short" rot="R180"/>
<pin name="VSS@4" x="-149.86" y="38.1" length="short" direction="pwr"/>
<pin name="VDD@6" x="-114.3" y="68.58" length="short" direction="pwr" rot="R180"/>
<pin name="PB12" x="-180.34" y="63.5" length="short" rot="R180"/>
<pin name="PB13" x="-180.34" y="60.96" length="short" rot="R180"/>
<pin name="PB14" x="-180.34" y="58.42" length="short" rot="R180"/>
<pin name="PB15" x="-180.34" y="55.88" length="short" rot="R180"/>
<pin name="PD8" x="-180.34" y="17.78" length="short" rot="R180"/>
<pin name="PD9" x="-180.34" y="15.24" length="short" rot="R180"/>
<pin name="PD10" x="-180.34" y="12.7" length="short" rot="R180"/>
<pin name="PD11" x="-180.34" y="10.16" length="short" rot="R180"/>
<pin name="PD12" x="-180.34" y="7.62" length="short" rot="R180"/>
<pin name="PD13" x="-180.34" y="5.08" length="short" rot="R180"/>
<pin name="VSS@5" x="-149.86" y="35.56" length="short" direction="pwr"/>
<pin name="VDD@7" x="-114.3" y="66.04" length="short" direction="pwr" rot="R180"/>
<pin name="PD14" x="-180.34" y="2.54" length="short" rot="R180"/>
<pin name="PD15" x="-180.34" y="0" length="short" rot="R180"/>
<pin name="PG2" x="-205.74" y="-78.74" length="short"/>
<pin name="PG3" x="-205.74" y="-81.28" length="short"/>
<pin name="PG4" x="-205.74" y="-83.82" length="short"/>
<pin name="PG5" x="-205.74" y="-86.36" length="short"/>
<pin name="PG6" x="-205.74" y="-88.9" length="short"/>
<pin name="PG7" x="-205.74" y="-91.44" length="short"/>
<pin name="PG8" x="-205.74" y="-93.98" length="short"/>
<pin name="VSS@6" x="-149.86" y="33.02" length="short" direction="pwr"/>
<pin name="VDD@8" x="-114.3" y="63.5" length="short" direction="pwr" rot="R180"/>
<pin name="PC6" x="-205.74" y="22.86" length="short"/>
<pin name="PC7" x="-205.74" y="20.32" length="short"/>
<pin name="PC8" x="-205.74" y="17.78" length="short"/>
<pin name="PC9" x="-205.74" y="15.24" length="short"/>
<pin name="PA8" x="-205.74" y="73.66" length="short"/>
<pin name="PA9" x="-205.74" y="71.12" length="short"/>
<pin name="PA10" x="-205.74" y="68.58" length="short"/>
<pin name="PA11" x="-205.74" y="66.04" length="short"/>
<pin name="PA12" x="-205.74" y="63.5" length="short"/>
<pin name="PA13" x="-205.74" y="60.96" length="short"/>
<pin name="VCAP_2" x="-114.3" y="20.32" length="short" direction="out" rot="R180"/>
<pin name="VSS@7" x="-149.86" y="30.48" length="short" direction="pwr"/>
<pin name="VDD@9" x="-114.3" y="60.96" length="short" direction="pwr" rot="R180"/>
<pin name="PH13" x="-180.34" y="-106.68" length="short" rot="R180"/>
<pin name="PH14" x="-180.34" y="-109.22" length="short" rot="R180"/>
<pin name="PH15" x="-180.34" y="-111.76" length="short" rot="R180"/>
<pin name="PI0" x="-149.86" y="86.36" length="short"/>
<pin name="PI1" x="-149.86" y="83.82" length="short"/>
<pin name="PI2" x="-149.86" y="81.28" length="short"/>
<pin name="PI3" x="-149.86" y="78.74" length="short"/>
<pin name="VSS@8" x="-149.86" y="27.94" length="short" direction="pwr"/>
<pin name="VDD@10" x="-114.3" y="58.42" length="short" direction="pwr" rot="R180"/>
<pin name="PA14" x="-205.74" y="58.42" length="short"/>
<pin name="PA15" x="-205.74" y="55.88" length="short"/>
<pin name="PC10" x="-205.74" y="12.7" length="short"/>
<pin name="PC11" x="-205.74" y="10.16" length="short"/>
<pin name="PC12" x="-205.74" y="7.62" length="short"/>
<pin name="PD0" x="-180.34" y="38.1" length="short" rot="R180"/>
<pin name="PD1" x="-180.34" y="35.56" length="short" rot="R180"/>
<pin name="PD2" x="-180.34" y="33.02" length="short" rot="R180"/>
<pin name="PD3" x="-180.34" y="30.48" length="short" rot="R180"/>
<pin name="PD4" x="-180.34" y="27.94" length="short" rot="R180"/>
<pin name="PD5" x="-180.34" y="25.4" length="short" rot="R180"/>
<pin name="VSS@9" x="-149.86" y="25.4" length="short" direction="pwr"/>
<pin name="VDD@11" x="-114.3" y="55.88" length="short" direction="pwr" rot="R180"/>
<pin name="PD6" x="-180.34" y="22.86" length="short" rot="R180"/>
<pin name="PD7" x="-180.34" y="20.32" length="short" rot="R180"/>
<pin name="PG9" x="-205.74" y="-96.52" length="short"/>
<pin name="PG10" x="-205.74" y="-99.06" length="short"/>
<pin name="PG11" x="-205.74" y="-101.6" length="short"/>
<pin name="PG12" x="-205.74" y="-104.14" length="short"/>
<pin name="PG13" x="-205.74" y="-106.68" length="short"/>
<pin name="PG14" x="-205.74" y="-109.22" length="short"/>
<pin name="VSS@10" x="-149.86" y="22.86" length="short" direction="pwr"/>
<pin name="VDD@12" x="-114.3" y="53.34" length="short" direction="pwr" rot="R180"/>
<pin name="PG15" x="-205.74" y="-111.76" length="short"/>
<pin name="PB3" x="-180.34" y="86.36" length="short" rot="R180"/>
<pin name="PB4" x="-180.34" y="83.82" length="short" rot="R180"/>
<pin name="PB5" x="-180.34" y="81.28" length="short" rot="R180"/>
<pin name="PB6" x="-180.34" y="78.74" length="short" rot="R180"/>
<pin name="PB7" x="-180.34" y="76.2" length="short" rot="R180"/>
<pin name="BOOT0" x="-149.86" y="53.34" length="short" direction="in"/>
<pin name="PB8" x="-180.34" y="73.66" length="short" rot="R180"/>
<pin name="PB9" x="-180.34" y="71.12" length="short" rot="R180"/>
<pin name="PE0" x="-205.74" y="-17.78" length="short"/>
<pin name="PE1" x="-205.74" y="-20.32" length="short"/>
<pin name="PDR_ON" x="-114.3" y="30.48" length="short" direction="in" rot="R180"/>
<pin name="VDD@13" x="-114.3" y="50.8" length="short" direction="pwr" rot="R180"/>
<pin name="PI4" x="-149.86" y="76.2" length="short"/>
<pin name="PI5" x="-149.86" y="73.66" length="short"/>
<pin name="PI6" x="-149.86" y="71.12" length="short"/>
<pin name="PI7" x="-149.86" y="68.58" length="short"/>
<text x="-203.2" y="99.06" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="-203.2" y="50.8" size="1.778" layer="96">&gt;VALUE</text>
<wire x1="-203.2" y1="96.52" x2="-203.2" y2="53.34" width="0.254" layer="94"/>
<wire x1="-203.2" y1="53.34" x2="-182.88" y2="53.34" width="0.254" layer="94"/>
<wire x1="-182.88" y1="53.34" x2="-182.88" y2="96.52" width="0.254" layer="94"/>
<wire x1="-182.88" y1="96.52" x2="-203.2" y2="96.52" width="0.254" layer="94"/>
<wire x1="-203.2" y1="40.64" x2="-203.2" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-203.2" y1="-2.54" x2="-182.88" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-182.88" y1="-2.54" x2="-182.88" y2="40.64" width="0.254" layer="94"/>
<wire x1="-182.88" y1="40.64" x2="-203.2" y2="40.64" width="0.254" layer="94"/>
<wire x1="-203.2" y1="-15.24" x2="-182.88" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-182.88" y1="-15.24" x2="-182.88" y2="-58.42" width="0.254" layer="94"/>
<wire x1="-182.88" y1="-58.42" x2="-203.2" y2="-58.42" width="0.254" layer="94"/>
<wire x1="-203.2" y1="-58.42" x2="-203.2" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-203.2" y1="-71.12" x2="-182.88" y2="-71.12" width="0.254" layer="94"/>
<wire x1="-182.88" y1="-71.12" x2="-182.88" y2="-114.3" width="0.254" layer="94"/>
<wire x1="-182.88" y1="-114.3" x2="-203.2" y2="-114.3" width="0.254" layer="94"/>
<wire x1="-203.2" y1="-114.3" x2="-203.2" y2="-71.12" width="0.254" layer="94"/>
<text x="-203.2" y="43.18" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="-203.2" y="-12.7" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="-203.2" y="-68.58" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="-203.2" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<text x="-203.2" y="-60.96" size="1.778" layer="96">&gt;VALUE</text>
<text x="-203.2" y="-116.84" size="1.778" layer="96">&gt;VALUE</text>
<wire x1="-147.32" y1="88.9" x2="-147.32" y2="17.78" width="0.254" layer="94"/>
<wire x1="-147.32" y1="88.9" x2="-116.84" y2="88.9" width="0.254" layer="94"/>
<wire x1="-116.84" y1="88.9" x2="-116.84" y2="17.78" width="0.254" layer="94"/>
<wire x1="-147.32" y1="17.78" x2="-116.84" y2="17.78" width="0.254" layer="94"/>
<text x="-147.32" y="91.44" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="-147.32" y="15.24" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="STM32PAPB">
<pin name="PA0" x="0" y="0" length="short"/>
<pin name="PA1" x="0" y="-2.54" length="short"/>
<pin name="PA2" x="0" y="-5.08" length="short"/>
<pin name="PA3" x="0" y="-7.62" length="short"/>
<pin name="PA4" x="0" y="-10.16" length="short"/>
<pin name="PA5" x="0" y="-12.7" length="short"/>
<pin name="PA6" x="0" y="-15.24" length="short"/>
<pin name="PA7" x="0" y="-17.78" length="short"/>
<pin name="PB0" x="25.4" y="0" length="short" rot="R180"/>
<pin name="PB1" x="25.4" y="-2.54" length="short" rot="R180"/>
<pin name="PB2" x="25.4" y="-5.08" length="short" rot="R180"/>
<pin name="PB10" x="25.4" y="-25.4" length="short" rot="R180"/>
<pin name="PB11" x="25.4" y="-27.94" length="short" rot="R180"/>
<pin name="PB12" x="25.4" y="-30.48" length="short" rot="R180"/>
<pin name="PB13" x="25.4" y="-33.02" length="short" rot="R180"/>
<pin name="PB14" x="25.4" y="-35.56" length="short" rot="R180"/>
<pin name="PB15" x="25.4" y="-38.1" length="short" rot="R180"/>
<pin name="PA8" x="0" y="-20.32" length="short"/>
<pin name="PA9" x="0" y="-22.86" length="short"/>
<pin name="PA10" x="0" y="-25.4" length="short"/>
<pin name="PA11" x="0" y="-27.94" length="short"/>
<pin name="PA12" x="0" y="-30.48" length="short"/>
<pin name="PA13" x="0" y="-33.02" length="short"/>
<pin name="PA14" x="0" y="-35.56" length="short"/>
<pin name="PA15" x="0" y="-38.1" length="short"/>
<pin name="PB3" x="25.4" y="-7.62" length="short" rot="R180"/>
<pin name="PB4" x="25.4" y="-10.16" length="short" rot="R180"/>
<pin name="PB5" x="25.4" y="-12.7" length="short" rot="R180"/>
<pin name="PB6" x="25.4" y="-15.24" length="short" rot="R180"/>
<pin name="PB7" x="25.4" y="-17.78" length="short" rot="R180"/>
<pin name="PB8" x="25.4" y="-20.32" length="short" rot="R180"/>
<pin name="PB9" x="25.4" y="-22.86" length="short" rot="R180"/>
<text x="2.54" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<wire x1="2.54" y1="2.54" x2="2.54" y2="-40.64" width="0.254" layer="94"/>
<wire x1="2.54" y1="-40.64" x2="22.86" y2="-40.64" width="0.254" layer="94"/>
<wire x1="22.86" y1="-40.64" x2="22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
</symbol>
<symbol name="STM32PCPD">
<pin name="PC13" x="-2.54" y="-33.02" length="short"/>
<pin name="PC14" x="-2.54" y="-35.56" length="short"/>
<pin name="PC15" x="-2.54" y="-38.1" length="short"/>
<pin name="PC0" x="-2.54" y="0" length="short"/>
<pin name="PC1" x="-2.54" y="-2.54" length="short"/>
<pin name="PC2" x="-2.54" y="-5.08" length="short"/>
<pin name="PC3" x="-2.54" y="-7.62" length="short"/>
<pin name="PC4" x="-2.54" y="-10.16" length="short"/>
<pin name="PC5" x="-2.54" y="-12.7" length="short"/>
<pin name="PD8" x="22.86" y="-20.32" length="short" rot="R180"/>
<pin name="PD9" x="22.86" y="-22.86" length="short" rot="R180"/>
<pin name="PD10" x="22.86" y="-25.4" length="short" rot="R180"/>
<pin name="PD11" x="22.86" y="-27.94" length="short" rot="R180"/>
<pin name="PD12" x="22.86" y="-30.48" length="short" rot="R180"/>
<pin name="PD13" x="22.86" y="-33.02" length="short" rot="R180"/>
<pin name="PD14" x="22.86" y="-35.56" length="short" rot="R180"/>
<pin name="PD15" x="22.86" y="-38.1" length="short" rot="R180"/>
<pin name="PC6" x="-2.54" y="-15.24" length="short"/>
<pin name="PC7" x="-2.54" y="-17.78" length="short"/>
<pin name="PC8" x="-2.54" y="-20.32" length="short"/>
<pin name="PC9" x="-2.54" y="-22.86" length="short"/>
<pin name="PC10" x="-2.54" y="-25.4" length="short"/>
<pin name="PC11" x="-2.54" y="-27.94" length="short"/>
<pin name="PC12" x="-2.54" y="-30.48" length="short"/>
<pin name="PD0" x="22.86" y="0" length="short" rot="R180"/>
<pin name="PD1" x="22.86" y="-2.54" length="short" rot="R180"/>
<pin name="PD2" x="22.86" y="-5.08" length="short" rot="R180"/>
<pin name="PD3" x="22.86" y="-7.62" length="short" rot="R180"/>
<pin name="PD4" x="22.86" y="-10.16" length="short" rot="R180"/>
<pin name="PD5" x="22.86" y="-12.7" length="short" rot="R180"/>
<pin name="PD6" x="22.86" y="-15.24" length="short" rot="R180"/>
<pin name="PD7" x="22.86" y="-17.78" length="short" rot="R180"/>
<wire x1="0" y1="2.54" x2="0" y2="-40.64" width="0.254" layer="94"/>
<wire x1="0" y1="-40.64" x2="20.32" y2="-40.64" width="0.254" layer="94"/>
<wire x1="20.32" y1="-40.64" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="2.54" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
</symbol>
<symbol name="STM32PEPF">
<pin name="PE2" x="-2.54" y="-5.08" length="short"/>
<pin name="PE3" x="-2.54" y="-7.62" length="short"/>
<pin name="PE4" x="-2.54" y="-10.16" length="short"/>
<pin name="PE5" x="-2.54" y="-12.7" length="short"/>
<pin name="PE6" x="-2.54" y="-15.24" length="short"/>
<pin name="PF0" x="22.86" y="0" length="short" rot="R180"/>
<pin name="PF1" x="22.86" y="-2.54" length="short" rot="R180"/>
<pin name="PF2" x="22.86" y="-5.08" length="short" rot="R180"/>
<pin name="PF3" x="22.86" y="-7.62" length="short" rot="R180"/>
<pin name="PF4" x="22.86" y="-10.16" length="short" rot="R180"/>
<pin name="PF5" x="22.86" y="-12.7" length="short" rot="R180"/>
<pin name="PF6" x="22.86" y="-15.24" length="short" rot="R180"/>
<pin name="PF7" x="22.86" y="-17.78" length="short" rot="R180"/>
<pin name="PF8" x="22.86" y="-20.32" length="short" rot="R180"/>
<pin name="PF9" x="22.86" y="-22.86" length="short" rot="R180"/>
<pin name="PF10" x="22.86" y="-25.4" length="short" rot="R180"/>
<pin name="PF11" x="22.86" y="-27.94" length="short" rot="R180"/>
<pin name="PF12" x="22.86" y="-30.48" length="short" rot="R180"/>
<pin name="PF13" x="22.86" y="-33.02" length="short" rot="R180"/>
<pin name="PF14" x="22.86" y="-35.56" length="short" rot="R180"/>
<pin name="PF15" x="22.86" y="-38.1" length="short" rot="R180"/>
<pin name="PE7" x="-2.54" y="-17.78" length="short"/>
<pin name="PE8" x="-2.54" y="-20.32" length="short"/>
<pin name="PE9" x="-2.54" y="-22.86" length="short"/>
<pin name="PE10" x="-2.54" y="-25.4" length="short"/>
<pin name="PE11" x="-2.54" y="-27.94" length="short"/>
<pin name="PE12" x="-2.54" y="-30.48" length="short"/>
<pin name="PE13" x="-2.54" y="-33.02" length="short"/>
<pin name="PE14" x="-2.54" y="-35.56" length="short"/>
<pin name="PE15" x="-2.54" y="-38.1" length="short"/>
<pin name="PE0" x="-2.54" y="0" length="short"/>
<pin name="PE1" x="-2.54" y="-2.54" length="short"/>
<wire x1="0" y1="2.54" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="2.54" x2="20.32" y2="-40.64" width="0.254" layer="94"/>
<wire x1="20.32" y1="-40.64" x2="0" y2="-40.64" width="0.254" layer="94"/>
<wire x1="0" y1="-40.64" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
</symbol>
<symbol name="STM32PGPH">
<pin name="PH0" x="22.86" y="0" length="short" rot="R180"/>
<pin name="PH1" x="22.86" y="-2.54" length="short" rot="R180"/>
<pin name="PH2" x="22.86" y="-5.08" length="short" rot="R180"/>
<pin name="PH3" x="22.86" y="-7.62" length="short" rot="R180"/>
<pin name="PH4" x="22.86" y="-10.16" length="short" rot="R180"/>
<pin name="PH5" x="22.86" y="-12.7" length="short" rot="R180"/>
<pin name="PG0" x="-2.54" y="0" length="short"/>
<pin name="PG1" x="-2.54" y="-2.54" length="short"/>
<pin name="PH6" x="22.86" y="-15.24" length="short" rot="R180"/>
<pin name="PH7" x="22.86" y="-17.78" length="short" rot="R180"/>
<pin name="PH8" x="22.86" y="-20.32" length="short" rot="R180"/>
<pin name="PH9" x="22.86" y="-22.86" length="short" rot="R180"/>
<pin name="PH10" x="22.86" y="-25.4" length="short" rot="R180"/>
<pin name="PH11" x="22.86" y="-27.94" length="short" rot="R180"/>
<pin name="PH12" x="22.86" y="-30.48" length="short" rot="R180"/>
<pin name="PG2" x="-2.54" y="-5.08" length="short"/>
<pin name="PG3" x="-2.54" y="-7.62" length="short"/>
<pin name="PG4" x="-2.54" y="-10.16" length="short"/>
<pin name="PG5" x="-2.54" y="-12.7" length="short"/>
<pin name="PG6" x="-2.54" y="-15.24" length="short"/>
<pin name="PG7" x="-2.54" y="-17.78" length="short"/>
<pin name="PG8" x="-2.54" y="-20.32" length="short"/>
<pin name="PH13" x="22.86" y="-33.02" length="short" rot="R180"/>
<pin name="PH14" x="22.86" y="-35.56" length="short" rot="R180"/>
<pin name="PH15" x="22.86" y="-38.1" length="short" rot="R180"/>
<pin name="PG9" x="-2.54" y="-22.86" length="short"/>
<pin name="PG10" x="-2.54" y="-25.4" length="short"/>
<pin name="PG11" x="-2.54" y="-27.94" length="short"/>
<pin name="PG12" x="-2.54" y="-30.48" length="short"/>
<pin name="PG13" x="-2.54" y="-33.02" length="short"/>
<pin name="PG14" x="-2.54" y="-35.56" length="short"/>
<pin name="PG15" x="-2.54" y="-38.1" length="short"/>
<wire x1="0" y1="2.54" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="2.54" x2="20.32" y2="-40.64" width="0.254" layer="94"/>
<wire x1="20.32" y1="-40.64" x2="0" y2="-40.64" width="0.254" layer="94"/>
<wire x1="0" y1="-40.64" x2="0" y2="2.54" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
</symbol>
<symbol name="STM32F4XXIXT_5">
<pin name="VBAT" x="33.02" y="0" length="short" direction="pwr" rot="R180"/>
<pin name="PI8" x="-2.54" y="-20.32" length="short"/>
<pin name="PI9" x="-2.54" y="-22.86" length="short"/>
<pin name="PI10" x="-2.54" y="-25.4" length="short"/>
<pin name="PI11" x="-2.54" y="-27.94" length="short"/>
<pin name="VSS" x="-2.54" y="-38.1" length="short" direction="pwr"/>
<pin name="VDD" x="33.02" y="-2.54" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@1" x="-2.54" y="-40.64" length="short" direction="pwr"/>
<pin name="VDD@1" x="33.02" y="-5.08" length="short" direction="pwr" rot="R180"/>
<pin name="NRST" x="33.02" y="-50.8" length="short" direction="in" rot="R180"/>
<pin name="VDDA" x="33.02" y="-43.18" length="short" direction="pwr" rot="R180"/>
<pin name="VSSA" x="-2.54" y="-66.04" length="short" direction="pwr"/>
<pin name="VREF+" x="33.02" y="-40.64" length="short" direction="in" rot="R180"/>
<pin name="VDDA@1" x="33.02" y="-45.72" length="short" direction="pwr" rot="R180"/>
<pin name="BYPASS_REG" x="33.02" y="-58.42" length="short" direction="in" rot="R180"/>
<pin name="VDD@2" x="33.02" y="-7.62" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@2" x="-2.54" y="-43.18" length="short" direction="pwr"/>
<pin name="VDD@3" x="33.02" y="-10.16" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@3" x="-2.54" y="-45.72" length="short" direction="pwr"/>
<pin name="VDD@4" x="33.02" y="-12.7" length="short" direction="pwr" rot="R180"/>
<pin name="VCAP_1" x="33.02" y="-63.5" length="short" direction="out" rot="R180"/>
<pin name="VDD@5" x="33.02" y="-15.24" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@4" x="-2.54" y="-48.26" length="short" direction="pwr"/>
<pin name="VDD@6" x="33.02" y="-17.78" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@5" x="-2.54" y="-50.8" length="short" direction="pwr"/>
<pin name="VDD@7" x="33.02" y="-20.32" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@6" x="-2.54" y="-53.34" length="short" direction="pwr"/>
<pin name="VDD@8" x="33.02" y="-22.86" length="short" direction="pwr" rot="R180"/>
<pin name="VCAP_2" x="33.02" y="-66.04" length="short" direction="out" rot="R180"/>
<pin name="VSS@7" x="-2.54" y="-55.88" length="short" direction="pwr"/>
<pin name="VDD@9" x="33.02" y="-25.4" length="short" direction="pwr" rot="R180"/>
<pin name="PI0" x="-2.54" y="0" length="short"/>
<pin name="PI1" x="-2.54" y="-2.54" length="short"/>
<pin name="PI2" x="-2.54" y="-5.08" length="short"/>
<pin name="PI3" x="-2.54" y="-7.62" length="short"/>
<pin name="VSS@8" x="-2.54" y="-58.42" length="short" direction="pwr"/>
<pin name="VDD@10" x="33.02" y="-27.94" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@9" x="-2.54" y="-60.96" length="short" direction="pwr"/>
<pin name="VDD@11" x="33.02" y="-30.48" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@10" x="-2.54" y="-63.5" length="short" direction="pwr"/>
<pin name="VDD@12" x="33.02" y="-33.02" length="short" direction="pwr" rot="R180"/>
<pin name="BOOT0" x="-2.54" y="-33.02" length="short" direction="in"/>
<pin name="PDR_ON" x="33.02" y="-55.88" length="short" direction="in" rot="R180"/>
<pin name="VDD@13" x="33.02" y="-35.56" length="short" direction="pwr" rot="R180"/>
<pin name="PI4" x="-2.54" y="-10.16" length="short"/>
<pin name="PI5" x="-2.54" y="-12.7" length="short"/>
<pin name="PI6" x="-2.54" y="-15.24" length="short"/>
<pin name="PI7" x="-2.54" y="-17.78" length="short"/>
<wire x1="0" y1="2.54" x2="0" y2="-68.58" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="30.48" y2="2.54" width="0.254" layer="94"/>
<wire x1="30.48" y1="2.54" x2="30.48" y2="-68.58" width="0.254" layer="94"/>
<wire x1="0" y1="-68.58" x2="30.48" y2="-68.58" width="0.254" layer="94"/>
<text x="0" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="0" y="-71.12" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="L">
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="5.08" y1="0" x2="7.62" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="7.62" y1="0" x2="10.16" y2="0" width="0.254" layer="94" curve="-180"/>
<pin name="P$1" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="P$2" x="12.7" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<text x="0" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="0" y="-2.54" size="1.778" layer="96" align="top-left">&gt;VALUE</text>
</symbol>
<symbol name="CPOL">
<wire x1="-1.524" y1="-0.889" x2="1.524" y2="-0.889" width="0.254" layer="94"/>
<wire x1="1.524" y1="-0.889" x2="1.524" y2="0" width="0.254" layer="94"/>
<wire x1="-1.524" y1="0" x2="-1.524" y2="-0.889" width="0.254" layer="94"/>
<wire x1="-1.524" y1="0" x2="1.524" y2="0" width="0.254" layer="94"/>
<text x="1.143" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="-0.5842" y="0.4064" size="1.27" layer="94" rot="R90">+</text>
<text x="1.143" y="-4.5974" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-1.651" y1="-2.54" x2="1.651" y2="-1.651" layer="94"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
</symbol>
<symbol name="STM32F4XXVXT">
<pin name="VBAT" x="35.56" y="-17.78" length="short" direction="pwr" rot="R180"/>
<pin name="VSS" x="0" y="-58.42" length="short" direction="pwr"/>
<pin name="VDD" x="35.56" y="-20.32" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@1" x="0" y="-60.96" length="short" direction="pwr"/>
<pin name="VDD@1" x="35.56" y="-22.86" length="short" direction="pwr" rot="R180"/>
<pin name="NRST" x="0" y="-43.18" length="short" direction="in"/>
<pin name="VDDA" x="35.56" y="-58.42" length="short" direction="pwr" rot="R180"/>
<pin name="VSSA" x="0" y="-66.04" length="short" direction="pwr"/>
<pin name="VREF+" x="35.56" y="-45.72" length="short" direction="in" rot="R180"/>
<pin name="VDD@2" x="35.56" y="-25.4" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@2" x="0" y="-63.5" length="short" direction="pwr"/>
<pin name="VDD@3" x="35.56" y="-27.94" length="short" direction="pwr" rot="R180"/>
<pin name="VDD@4" x="35.56" y="-30.48" length="short" direction="pwr" rot="R180"/>
<pin name="VCAP_1" x="35.56" y="-63.5" length="short" direction="out" rot="R180"/>
<pin name="VDD@5" x="35.56" y="-33.02" length="short" direction="pwr" rot="R180"/>
<pin name="VCAP_2" x="35.56" y="-66.04" length="short" direction="out" rot="R180"/>
<pin name="PH0" x="35.56" y="0" length="short" rot="R180"/>
<pin name="PH1" x="35.56" y="-12.7" length="short" rot="R180"/>
<pin name="BOOT0" x="0" y="-50.8" length="short" direction="in"/>
<pin name="VSS@3" x="0" y="-55.88" length="short" direction="in"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="-68.58" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="33.02" y2="2.54" width="0.254" layer="94"/>
<wire x1="33.02" y1="2.54" x2="33.02" y2="-68.58" width="0.254" layer="94"/>
<wire x1="2.54" y1="-68.58" x2="33.02" y2="-68.58" width="0.254" layer="94"/>
<text x="2.54" y="5.08" size="1.778" layer="95" align="top-left">&gt;NAME</text>
<text x="2.54" y="-71.12" size="1.778" layer="96">&gt;VALUE</text>
<pin name="PE2" x="0" y="-5.08" length="short"/>
<pin name="PE3" x="0" y="-7.62" length="short"/>
<pin name="PE4" x="0" y="-10.16" length="short"/>
<pin name="PE5" x="0" y="-12.7" length="short"/>
<pin name="PE6" x="0" y="-15.24" length="short"/>
<pin name="PE7" x="0" y="-17.78" length="short"/>
<pin name="PE8" x="0" y="-20.32" length="short"/>
<pin name="PE9" x="0" y="-22.86" length="short"/>
<pin name="PE10" x="0" y="-25.4" length="short"/>
<pin name="PE11" x="0" y="-27.94" length="short"/>
<pin name="PE12" x="0" y="-30.48" length="short"/>
<pin name="PE13" x="0" y="-33.02" length="short"/>
<pin name="PE14" x="0" y="-35.56" length="short"/>
<pin name="PE15" x="0" y="-38.1" length="short"/>
<pin name="PE0" x="0" y="0" length="short"/>
<pin name="PE1" x="0" y="-2.54" length="short"/>
</symbol>
<symbol name="PINHD5">
<wire x1="-3.81" y1="-7.62" x2="3.81" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-7.62" x2="3.81" y2="7.62" width="0.4064" layer="94"/>
<wire x1="3.81" y1="7.62" x2="-3.81" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="7.62" x2="-3.81" y2="-7.62" width="0.4064" layer="94"/>
<text x="-3.81" y="8.255" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="0" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="0" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="0" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="0" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="5" x="0" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CS43L22" prefix="DD">
<description>&lt;b&gt;CS43L22&lt;/b&gt; &lt;font color="red"&gt;edit this description&lt;/font&gt;&lt;p&gt;
Auto generated by &lt;i&gt;make-symbol-device-package-bsdl.ulp Rev. 43&lt;/i&gt;&lt;br&gt;
Source: CS43L22.txt</description>
<gates>
<gate name="DD$1" symbol="CS43L22" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN40-6X6">
<connects>
<connect gate="DD$1" pin="#RESET" pad="32"/>
<connect gate="DD$1" pin="+VHP" pad="13"/>
<connect gate="DD$1" pin="-VHPFILT" pad="10"/>
<connect gate="DD$1" pin="AD0" pad="3"/>
<connect gate="DD$1" pin="AFILTA" pad="27"/>
<connect gate="DD$1" pin="AFILTB" pad="28"/>
<connect gate="DD$1" pin="AGND" pad="17"/>
<connect gate="DD$1" pin="AIN1A" pad="29"/>
<connect gate="DD$1" pin="AIN1B" pad="30"/>
<connect gate="DD$1" pin="AIN2A" pad="25"/>
<connect gate="DD$1" pin="AIN2B" pad="26"/>
<connect gate="DD$1" pin="AIN3A" pad="23"/>
<connect gate="DD$1" pin="AIN3B" pad="24"/>
<connect gate="DD$1" pin="AIN4A" pad="21"/>
<connect gate="DD$1" pin="AIN4B" pad="22"/>
<connect gate="DD$1" pin="DGND" pad="35"/>
<connect gate="DD$1" pin="FILT+" pad="18"/>
<connect gate="DD$1" pin="FLYN" pad="11"/>
<connect gate="DD$1" pin="FLYP" pad="12"/>
<connect gate="DD$1" pin="GND/PAD" pad="EXP@3 EXP@4 EXP@5 EXP@9"/>
<connect gate="DD$1" pin="HP/LINE_OUTA" pad="15"/>
<connect gate="DD$1" pin="HP/LINE_OUTB" pad="14"/>
<connect gate="DD$1" pin="LRCK" pad="40"/>
<connect gate="DD$1" pin="MCLK" pad="37"/>
<connect gate="DD$1" pin="SCL" pad="2"/>
<connect gate="DD$1" pin="SCLK" pad="38"/>
<connect gate="DD$1" pin="SDA" pad="1"/>
<connect gate="DD$1" pin="SDIN" pad="39"/>
<connect gate="DD$1" pin="SPKR/HP" pad="31"/>
<connect gate="DD$1" pin="SPKR_OUTA+" pad="4"/>
<connect gate="DD$1" pin="SPKR_OUTA-" pad="6"/>
<connect gate="DD$1" pin="SPKR_OUTB+" pad="7"/>
<connect gate="DD$1" pin="SPKR_OUTB-" pad="9"/>
<connect gate="DD$1" pin="TSTO" pad="20"/>
<connect gate="DD$1" pin="TSTO@1" pad="36"/>
<connect gate="DD$1" pin="VA" pad="16"/>
<connect gate="DD$1" pin="VD" pad="34"/>
<connect gate="DD$1" pin="VL" pad="33"/>
<connect gate="DD$1" pin="VP" pad="8"/>
<connect gate="DD$1" pin="VP@1" pad="5"/>
<connect gate="DD$1" pin="VQ" pad="19"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NOKIA1100_KEY_PAD" prefix="SB">
<gates>
<gate name="SB$1" symbol="NOKIA1100_KEY_PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="NOKIA1100_KEY_PAD">
<connects>
<connect gate="SB$1" pin="INNER" pad="INNER INNER2"/>
<connect gate="SB$1" pin="OUTER" pad="OUTER OUTER1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NOKIA1100_DISP" prefix="D">
<gates>
<gate name="D$1" symbol="NOKIA1100_DISP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="NOKIA1100_DISP">
<connects>
<connect gate="D$1" pin="#CS" pad="2"/>
<connect gate="D$1" pin="#RES" pad="1"/>
<connect gate="D$1" pin="BKL" pad="8"/>
<connect gate="D$1" pin="SCLK" pad="5"/>
<connect gate="D$1" pin="SDIN" pad="4"/>
<connect gate="D$1" pin="VDD1" pad="6"/>
<connect gate="D$1" pin="VDD2" pad="7"/>
<connect gate="D$1" pin="VSS" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NOKIA1100_VIBRATOR" prefix="M">
<gates>
<gate name="M$1" symbol="NOKIA1100_VIBRATOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="NOKIA1100_VIBRATOR">
<connects>
<connect gate="M$1" pin="P$1" pad="1"/>
<connect gate="M$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NOKIA1100_BATTERY_CONN" prefix="B">
<gates>
<gate name="B$1" symbol="NOKIA1100_BATTERY_CONN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="NOKIA1100_BATTERY_CONN">
<connects>
<connect gate="B$1" pin="+" pad="+"/>
<connect gate="B$1" pin="-" pad="-"/>
<connect gate="B$1" pin="SRV" pad="SERV"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NOKIA1100_EXT_CONN" prefix="X">
<gates>
<gate name="X$1" symbol="NOKIA1100_EXT_CONN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="NOKIA1100_EXT_CONN">
<connects>
<connect gate="X$1" pin="A" pad="A"/>
<connect gate="X$1" pin="AGND" pad="AGND"/>
<connect gate="X$1" pin="B" pad="B"/>
<connect gate="X$1" pin="BTN" pad="BTN"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+2V5" prefix="+2V5">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+2V5" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="IRLML6402" prefix="VT">
<description>&lt;b&gt;HEXFET P-Channel Power MOSFET&lt;/b&gt;</description>
<gates>
<gate name="VT$1" symbol="MFPS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICRO3">
<connects>
<connect gate="VT$1" pin="D" pad="3"/>
<connect gate="VT$1" pin="G" pad="1"/>
<connect gate="VT$1" pin="S" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="IRLML2502" prefix="VT">
<description>HEXFET N-Channel Power MOSFET</description>
<gates>
<gate name="VT$1" symbol="MFNS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICRO3">
<connects>
<connect gate="VT$1" pin="D" pad="3"/>
<connect gate="VT$1" pin="G" pad="1"/>
<connect gate="VT$1" pin="S" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="+5V">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VBAT" prefix="VBAT">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="VBAT" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USBLC6-2SC6" prefix="DD">
<gates>
<gate name="DD$1" symbol="USBLC6-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23-6L">
<connects>
<connect gate="DD$1" pin="GND" pad="2"/>
<connect gate="DD$1" pin="IO1.1" pad="1"/>
<connect gate="DD$1" pin="IO1.2" pad="6"/>
<connect gate="DD$1" pin="IO2.1" pad="3"/>
<connect gate="DD$1" pin="IO2.2" pad="4"/>
<connect gate="DD$1" pin="VBUS" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROSD_CONN" prefix="X">
<gates>
<gate name="X$1" symbol="MICROSD_CONN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TFC-WPCE-08">
<connects>
<connect gate="X$1" pin="CK" pad="CLK"/>
<connect gate="X$1" pin="CMD" pad="CMD"/>
<connect gate="X$1" pin="D0" pad="DAT0"/>
<connect gate="X$1" pin="D1" pad="DAT1"/>
<connect gate="X$1" pin="D2" pad="DAT2"/>
<connect gate="X$1" pin="D3" pad="CD/DAT3"/>
<connect gate="X$1" pin="SH" pad="SH1 SH2 SH3 SH4"/>
<connect gate="X$1" pin="SNS1" pad="SNS1"/>
<connect gate="X$1" pin="SNS2" pad="SNS2"/>
<connect gate="X$1" pin="VDD" pad="VDD"/>
<connect gate="X$1" pin="VSS" pad="VSS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="R-EU_" prefix="R" uservalue="yes">
<description>&lt;B&gt;RESISTOR&lt;/B&gt;, European symbol</description>
<gates>
<gate name="G$1" symbol="R-EU" x="0" y="0"/>
</gates>
<devices>
<device name="R0402" package="R0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="R0603" package="R0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="R0805" package="R0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="R1206" package="R1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="C-EU" prefix="C" uservalue="yes">
<description>&lt;B&gt;CAPACITOR&lt;/B&gt;, European symbol</description>
<gates>
<gate name="G$1" symbol="C-EU" x="0" y="0"/>
</gates>
<devices>
<device name="C0402" package="C0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C0603" package="C0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C0805" package="C0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LTC4054ES5-4.2" prefix="DD">
<gates>
<gate name="G$1" symbol="LTC4054ES5" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TSOT23-5">
<connects>
<connect gate="G$1" pin="#CHRG" pad="1"/>
<connect gate="G$1" pin="BAT" pad="3"/>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="PROG" pad="5"/>
<connect gate="G$1" pin="VCC" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="AA112" prefix="D">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
germanium</description>
<gates>
<gate name="1" symbol="D" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DO07">
<connects>
<connect gate="1" pin="A" pad="A"/>
<connect gate="1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VD-SMA" prefix="VD" uservalue="yes">
<gates>
<gate name="G$1" symbol="D" x="-2.54" y="0"/>
</gates>
<devices>
<device name="" package="SMA">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BC550*" prefix="Q">
<description>&lt;b&gt;NPN Transistor&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="NPN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO92-EBC">
<connects>
<connect gate="G$1" pin="B" pad="B"/>
<connect gate="G$1" pin="C" pad="C"/>
<connect gate="G$1" pin="E" pad="E"/>
</connects>
<technologies>
<technology name="B"/>
<technology name="C"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VT_NPN_DIGITAL" prefix="VT" uservalue="yes">
<gates>
<gate name="G$1" symbol="VT_NPN_DIGITAL" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23-BEC">
<connects>
<connect gate="G$1" pin="B" pad="B"/>
<connect gate="G$1" pin="C" pad="C"/>
<connect gate="G$1" pin="E" pad="E"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ESDA6V1W5" prefix="VD">
<gates>
<gate name="G$1" symbol="ESDA6V1W5" x="-5.08" y="0"/>
</gates>
<devices>
<device name="" package="SOT323-5L">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
<connect gate="G$1" pin="P$3" pad="3"/>
<connect gate="G$1" pin="P$4" pad="4"/>
<connect gate="G$1" pin="P$5" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB3300" prefix="DD">
<description>&lt;b&gt;USB3300&lt;/b&gt; &lt;font color="red"&gt;edit this description&lt;/font&gt;&lt;p&gt;
Auto generated by &lt;i&gt;make-symbol-device-package-bsdl.ulp Rev. 43&lt;/i&gt;&lt;br&gt;
Source: USB3300.txt</description>
<gates>
<gate name="G$1" symbol="USB3300" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN32">
<connects>
<connect gate="G$1" pin="CLKOUT" pad="14"/>
<connect gate="G$1" pin="CPEN" pad="3"/>
<connect gate="G$1" pin="DATA0" pad="24"/>
<connect gate="G$1" pin="DATA1" pad="23"/>
<connect gate="G$1" pin="DATA2" pad="22"/>
<connect gate="G$1" pin="DATA3" pad="21"/>
<connect gate="G$1" pin="DATA4" pad="20"/>
<connect gate="G$1" pin="DATA5" pad="19"/>
<connect gate="G$1" pin="DATA6" pad="18"/>
<connect gate="G$1" pin="DATA7" pad="17"/>
<connect gate="G$1" pin="DIR" pad="12"/>
<connect gate="G$1" pin="DM" pad="8"/>
<connect gate="G$1" pin="DP" pad="7"/>
<connect gate="G$1" pin="EXTVBUS" pad="10"/>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="GND@1" pad="2"/>
<connect gate="G$1" pin="GND_FLAG" pad="P$1 P$2 P$3 P$4 P$5 P$6 P$7 P$8 P$9"/>
<connect gate="G$1" pin="ID" pad="5"/>
<connect gate="G$1" pin="NXT" pad="11"/>
<connect gate="G$1" pin="RBIAS" pad="32"/>
<connect gate="G$1" pin="REG_EN" pad="31"/>
<connect gate="G$1" pin="RESET" pad="9"/>
<connect gate="G$1" pin="STP" pad="13"/>
<connect gate="G$1" pin="VBUS" pad="4"/>
<connect gate="G$1" pin="VDD1_8" pad="15"/>
<connect gate="G$1" pin="VDD1_8@1" pad="26"/>
<connect gate="G$1" pin="VDD3_3" pad="6"/>
<connect gate="G$1" pin="VDD3_3@1" pad="16"/>
<connect gate="G$1" pin="VDD3_3@2" pad="25"/>
<connect gate="G$1" pin="VDD3_3@3" pad="30"/>
<connect gate="G$1" pin="VDDA1_8" pad="29"/>
<connect gate="G$1" pin="XI" pad="28"/>
<connect gate="G$1" pin="XO" pad="27"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB_MINI_CONN" prefix="XT" uservalue="yes">
<gates>
<gate name="G$1" symbol="USB_MINI_CONN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="32005-201">
<connects>
<connect gate="G$1" pin="DM" pad="2"/>
<connect gate="G$1" pin="DP" pad="3"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="SC" pad="4"/>
<connect gate="G$1" pin="SH" pad="M1 M2 M3 M4"/>
<connect gate="G$1" pin="VDD" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="QUARTZ_5MM" prefix="ZQ" uservalue="yes">
<gates>
<gate name="G$1" symbol="QUARTZ_5MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QUARTZ_5MM">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LIS302DL" prefix="DD">
<description>&lt;b&gt;LIS302DL&lt;/b&gt; &lt;font color="red"&gt;edit this description&lt;/font&gt;&lt;p&gt;
Auto generated by &lt;i&gt;make-symbol-device-package-bsdl.ulp Rev. 43&lt;/i&gt;&lt;br&gt;
Source: LIS302DL.txt</description>
<gates>
<gate name="G$1" symbol="LIS302DL" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LGA14">
<connects>
<connect gate="G$1" pin="CS.I2C_SPI" pad="7"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="GND@1" pad="5"/>
<connect gate="G$1" pin="GND@2" pad="10"/>
<connect gate="G$1" pin="GND@3" pad="2"/>
<connect gate="G$1" pin="INT1" pad="8"/>
<connect gate="G$1" pin="INT2" pad="9"/>
<connect gate="G$1" pin="RESERVED" pad="3"/>
<connect gate="G$1" pin="RESERVED@1" pad="11"/>
<connect gate="G$1" pin="SCL_SPC" pad="14"/>
<connect gate="G$1" pin="SDA_SDI_SDO" pad="13"/>
<connect gate="G$1" pin="SDO" pad="12"/>
<connect gate="G$1" pin="VDD" pad="6"/>
<connect gate="G$1" pin="VDD_IO" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LD3985MXXR" prefix="DA" uservalue="yes">
<gates>
<gate name="G$1" symbol="LD3985MXXR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TSOT23-5">
<connects>
<connect gate="G$1" pin="BYPASS" pad="4"/>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="INH" pad="3"/>
<connect gate="G$1" pin="VIN" pad="1"/>
<connect gate="G$1" pin="VOUT" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STM32F4XXIXT" prefix="DD" uservalue="yes">
<gates>
<gate name=".1" symbol="STM32PAPB" x="0" y="0"/>
<gate name=".2" symbol="STM32PCPD" x="35.56" y="0"/>
<gate name=".3" symbol="STM32PEPF" x="66.04" y="0"/>
<gate name=".4" symbol="STM32PGPH" x="96.52" y="0"/>
<gate name=".5" symbol="STM32F4XXIXT_5" x="129.54" y="0"/>
</gates>
<devices>
<device name="" package="LQFP176">
<connects>
<connect gate=".1" pin="PA0" pad="40"/>
<connect gate=".1" pin="PA1" pad="41"/>
<connect gate=".1" pin="PA10" pad="121"/>
<connect gate=".1" pin="PA11" pad="122"/>
<connect gate=".1" pin="PA12" pad="123"/>
<connect gate=".1" pin="PA13" pad="124"/>
<connect gate=".1" pin="PA14" pad="137"/>
<connect gate=".1" pin="PA15" pad="138"/>
<connect gate=".1" pin="PA2" pad="42"/>
<connect gate=".1" pin="PA3" pad="47"/>
<connect gate=".1" pin="PA4" pad="50"/>
<connect gate=".1" pin="PA5" pad="51"/>
<connect gate=".1" pin="PA6" pad="52"/>
<connect gate=".1" pin="PA7" pad="53"/>
<connect gate=".1" pin="PA8" pad="119"/>
<connect gate=".1" pin="PA9" pad="120"/>
<connect gate=".1" pin="PB0" pad="56"/>
<connect gate=".1" pin="PB1" pad="57"/>
<connect gate=".1" pin="PB10" pad="79"/>
<connect gate=".1" pin="PB11" pad="80"/>
<connect gate=".1" pin="PB12" pad="92"/>
<connect gate=".1" pin="PB13" pad="93"/>
<connect gate=".1" pin="PB14" pad="94"/>
<connect gate=".1" pin="PB15" pad="95"/>
<connect gate=".1" pin="PB2" pad="58"/>
<connect gate=".1" pin="PB3" pad="161"/>
<connect gate=".1" pin="PB4" pad="162"/>
<connect gate=".1" pin="PB5" pad="163"/>
<connect gate=".1" pin="PB6" pad="164"/>
<connect gate=".1" pin="PB7" pad="165"/>
<connect gate=".1" pin="PB8" pad="167"/>
<connect gate=".1" pin="PB9" pad="168"/>
<connect gate=".2" pin="PC0" pad="32"/>
<connect gate=".2" pin="PC1" pad="33"/>
<connect gate=".2" pin="PC10" pad="139"/>
<connect gate=".2" pin="PC11" pad="140"/>
<connect gate=".2" pin="PC12" pad="141"/>
<connect gate=".2" pin="PC13" pad="8"/>
<connect gate=".2" pin="PC14" pad="9"/>
<connect gate=".2" pin="PC15" pad="10"/>
<connect gate=".2" pin="PC2" pad="34"/>
<connect gate=".2" pin="PC3" pad="35"/>
<connect gate=".2" pin="PC4" pad="54"/>
<connect gate=".2" pin="PC5" pad="55"/>
<connect gate=".2" pin="PC6" pad="115"/>
<connect gate=".2" pin="PC7" pad="116"/>
<connect gate=".2" pin="PC8" pad="117"/>
<connect gate=".2" pin="PC9" pad="118"/>
<connect gate=".2" pin="PD0" pad="142"/>
<connect gate=".2" pin="PD1" pad="143"/>
<connect gate=".2" pin="PD10" pad="98"/>
<connect gate=".2" pin="PD11" pad="99"/>
<connect gate=".2" pin="PD12" pad="100"/>
<connect gate=".2" pin="PD13" pad="101"/>
<connect gate=".2" pin="PD14" pad="104"/>
<connect gate=".2" pin="PD15" pad="105"/>
<connect gate=".2" pin="PD2" pad="144"/>
<connect gate=".2" pin="PD3" pad="145"/>
<connect gate=".2" pin="PD4" pad="146"/>
<connect gate=".2" pin="PD5" pad="147"/>
<connect gate=".2" pin="PD6" pad="150"/>
<connect gate=".2" pin="PD7" pad="151"/>
<connect gate=".2" pin="PD8" pad="96"/>
<connect gate=".2" pin="PD9" pad="97"/>
<connect gate=".3" pin="PE0" pad="169"/>
<connect gate=".3" pin="PE1" pad="170"/>
<connect gate=".3" pin="PE10" pad="73"/>
<connect gate=".3" pin="PE11" pad="74"/>
<connect gate=".3" pin="PE12" pad="75"/>
<connect gate=".3" pin="PE13" pad="76"/>
<connect gate=".3" pin="PE14" pad="77"/>
<connect gate=".3" pin="PE15" pad="78"/>
<connect gate=".3" pin="PE2" pad="1"/>
<connect gate=".3" pin="PE3" pad="2"/>
<connect gate=".3" pin="PE4" pad="3"/>
<connect gate=".3" pin="PE5" pad="4"/>
<connect gate=".3" pin="PE6" pad="5"/>
<connect gate=".3" pin="PE7" pad="68"/>
<connect gate=".3" pin="PE8" pad="69"/>
<connect gate=".3" pin="PE9" pad="70"/>
<connect gate=".3" pin="PF0" pad="16"/>
<connect gate=".3" pin="PF1" pad="17"/>
<connect gate=".3" pin="PF10" pad="28"/>
<connect gate=".3" pin="PF11" pad="59"/>
<connect gate=".3" pin="PF12" pad="60"/>
<connect gate=".3" pin="PF13" pad="63"/>
<connect gate=".3" pin="PF14" pad="64"/>
<connect gate=".3" pin="PF15" pad="65"/>
<connect gate=".3" pin="PF2" pad="18"/>
<connect gate=".3" pin="PF3" pad="19"/>
<connect gate=".3" pin="PF4" pad="20"/>
<connect gate=".3" pin="PF5" pad="21"/>
<connect gate=".3" pin="PF6" pad="24"/>
<connect gate=".3" pin="PF7" pad="25"/>
<connect gate=".3" pin="PF8" pad="26"/>
<connect gate=".3" pin="PF9" pad="27"/>
<connect gate=".4" pin="PG0" pad="66"/>
<connect gate=".4" pin="PG1" pad="67"/>
<connect gate=".4" pin="PG10" pad="153"/>
<connect gate=".4" pin="PG11" pad="154"/>
<connect gate=".4" pin="PG12" pad="155"/>
<connect gate=".4" pin="PG13" pad="156"/>
<connect gate=".4" pin="PG14" pad="157"/>
<connect gate=".4" pin="PG15" pad="160"/>
<connect gate=".4" pin="PG2" pad="106"/>
<connect gate=".4" pin="PG3" pad="107"/>
<connect gate=".4" pin="PG4" pad="108"/>
<connect gate=".4" pin="PG5" pad="109"/>
<connect gate=".4" pin="PG6" pad="110"/>
<connect gate=".4" pin="PG7" pad="111"/>
<connect gate=".4" pin="PG8" pad="112"/>
<connect gate=".4" pin="PG9" pad="152"/>
<connect gate=".4" pin="PH0" pad="29"/>
<connect gate=".4" pin="PH1" pad="30"/>
<connect gate=".4" pin="PH10" pad="87"/>
<connect gate=".4" pin="PH11" pad="88"/>
<connect gate=".4" pin="PH12" pad="89"/>
<connect gate=".4" pin="PH13" pad="128"/>
<connect gate=".4" pin="PH14" pad="129"/>
<connect gate=".4" pin="PH15" pad="130"/>
<connect gate=".4" pin="PH2" pad="43"/>
<connect gate=".4" pin="PH3" pad="44"/>
<connect gate=".4" pin="PH4" pad="45"/>
<connect gate=".4" pin="PH5" pad="46"/>
<connect gate=".4" pin="PH6" pad="83"/>
<connect gate=".4" pin="PH7" pad="84"/>
<connect gate=".4" pin="PH8" pad="85"/>
<connect gate=".4" pin="PH9" pad="86"/>
<connect gate=".5" pin="BOOT0" pad="166"/>
<connect gate=".5" pin="BYPASS_REG" pad="48"/>
<connect gate=".5" pin="NRST" pad="31"/>
<connect gate=".5" pin="PDR_ON" pad="171"/>
<connect gate=".5" pin="PI0" pad="131"/>
<connect gate=".5" pin="PI1" pad="132"/>
<connect gate=".5" pin="PI10" pad="12"/>
<connect gate=".5" pin="PI11" pad="13"/>
<connect gate=".5" pin="PI2" pad="133"/>
<connect gate=".5" pin="PI3" pad="134"/>
<connect gate=".5" pin="PI4" pad="173"/>
<connect gate=".5" pin="PI5" pad="174"/>
<connect gate=".5" pin="PI6" pad="175"/>
<connect gate=".5" pin="PI7" pad="176"/>
<connect gate=".5" pin="PI8" pad="7"/>
<connect gate=".5" pin="PI9" pad="11"/>
<connect gate=".5" pin="VBAT" pad="6"/>
<connect gate=".5" pin="VCAP_1" pad="81"/>
<connect gate=".5" pin="VCAP_2" pad="125"/>
<connect gate=".5" pin="VDD" pad="15"/>
<connect gate=".5" pin="VDD@1" pad="23"/>
<connect gate=".5" pin="VDD@10" pad="136"/>
<connect gate=".5" pin="VDD@11" pad="149"/>
<connect gate=".5" pin="VDD@12" pad="159"/>
<connect gate=".5" pin="VDD@13" pad="172"/>
<connect gate=".5" pin="VDD@2" pad="49"/>
<connect gate=".5" pin="VDD@3" pad="62"/>
<connect gate=".5" pin="VDD@4" pad="72"/>
<connect gate=".5" pin="VDD@5" pad="82"/>
<connect gate=".5" pin="VDD@6" pad="91"/>
<connect gate=".5" pin="VDD@7" pad="103"/>
<connect gate=".5" pin="VDD@8" pad="114"/>
<connect gate=".5" pin="VDD@9" pad="127"/>
<connect gate=".5" pin="VDDA" pad="36"/>
<connect gate=".5" pin="VDDA@1" pad="39"/>
<connect gate=".5" pin="VREF+" pad="38"/>
<connect gate=".5" pin="VSS" pad="14"/>
<connect gate=".5" pin="VSS@1" pad="22"/>
<connect gate=".5" pin="VSS@10" pad="158"/>
<connect gate=".5" pin="VSS@2" pad="61"/>
<connect gate=".5" pin="VSS@3" pad="71"/>
<connect gate=".5" pin="VSS@4" pad="90"/>
<connect gate=".5" pin="VSS@5" pad="102"/>
<connect gate=".5" pin="VSS@6" pad="113"/>
<connect gate=".5" pin="VSS@7" pad="126"/>
<connect gate=".5" pin="VSS@8" pad="135"/>
<connect gate=".5" pin="VSS@9" pad="148"/>
<connect gate=".5" pin="VSSA" pad="37"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="FCM1608" prefix="L" uservalue="yes">
<gates>
<gate name="G$1" symbol="L" x="0" y="0"/>
</gates>
<devices>
<device name="" package="R0603">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="NOKIA1100_KEY_PAD_0" prefix="SB">
<gates>
<gate name="G$1" symbol="NOKIA1100_KEY_PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="NOKIA1100_KEY_PAD_0">
<connects>
<connect gate="G$1" pin="INNER" pad="INNER"/>
<connect gate="G$1" pin="OUTER" pad="OUTER OUTER1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CPOL-EU" prefix="C" uservalue="yes">
<description>&lt;B&gt;POLARIZED CAPACITOR&lt;/B&gt;, European symbol</description>
<gates>
<gate name="G$1" symbol="CPOL" x="0" y="0"/>
</gates>
<devices>
<device name="SMCA" package="SMC_A">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STM32F4XXVXT" prefix="DD" uservalue="yes">
<gates>
<gate name=".1" symbol="STM32PAPB" x="0" y="0"/>
<gate name=".2" symbol="STM32PCPD" x="35.56" y="0"/>
<gate name=".3" symbol="STM32F4XXVXT" x="63.5" y="0"/>
</gates>
<devices>
<device name="" package="LQFP100">
<connects>
<connect gate=".1" pin="PA0" pad="23"/>
<connect gate=".1" pin="PA1" pad="24"/>
<connect gate=".1" pin="PA10" pad="69"/>
<connect gate=".1" pin="PA11" pad="70"/>
<connect gate=".1" pin="PA12" pad="71"/>
<connect gate=".1" pin="PA13" pad="72"/>
<connect gate=".1" pin="PA14" pad="76"/>
<connect gate=".1" pin="PA15" pad="77"/>
<connect gate=".1" pin="PA2" pad="25"/>
<connect gate=".1" pin="PA3" pad="26"/>
<connect gate=".1" pin="PA4" pad="29"/>
<connect gate=".1" pin="PA5" pad="30"/>
<connect gate=".1" pin="PA6" pad="31"/>
<connect gate=".1" pin="PA7" pad="32"/>
<connect gate=".1" pin="PA8" pad="67"/>
<connect gate=".1" pin="PA9" pad="68"/>
<connect gate=".1" pin="PB0" pad="35"/>
<connect gate=".1" pin="PB1" pad="36"/>
<connect gate=".1" pin="PB10" pad="47"/>
<connect gate=".1" pin="PB11" pad="48"/>
<connect gate=".1" pin="PB12" pad="51"/>
<connect gate=".1" pin="PB13" pad="52"/>
<connect gate=".1" pin="PB14" pad="53"/>
<connect gate=".1" pin="PB15" pad="54"/>
<connect gate=".1" pin="PB2" pad="37"/>
<connect gate=".1" pin="PB3" pad="89"/>
<connect gate=".1" pin="PB4" pad="90"/>
<connect gate=".1" pin="PB5" pad="91"/>
<connect gate=".1" pin="PB6" pad="92"/>
<connect gate=".1" pin="PB7" pad="93"/>
<connect gate=".1" pin="PB8" pad="95"/>
<connect gate=".1" pin="PB9" pad="96"/>
<connect gate=".2" pin="PC0" pad="15"/>
<connect gate=".2" pin="PC1" pad="16"/>
<connect gate=".2" pin="PC10" pad="78"/>
<connect gate=".2" pin="PC11" pad="79"/>
<connect gate=".2" pin="PC12" pad="80"/>
<connect gate=".2" pin="PC13" pad="7"/>
<connect gate=".2" pin="PC14" pad="8"/>
<connect gate=".2" pin="PC15" pad="9"/>
<connect gate=".2" pin="PC2" pad="17"/>
<connect gate=".2" pin="PC3" pad="18"/>
<connect gate=".2" pin="PC4" pad="33"/>
<connect gate=".2" pin="PC5" pad="34"/>
<connect gate=".2" pin="PC6" pad="63"/>
<connect gate=".2" pin="PC7" pad="64"/>
<connect gate=".2" pin="PC8" pad="65"/>
<connect gate=".2" pin="PC9" pad="66"/>
<connect gate=".2" pin="PD0" pad="81"/>
<connect gate=".2" pin="PD1" pad="82"/>
<connect gate=".2" pin="PD10" pad="57"/>
<connect gate=".2" pin="PD11" pad="58"/>
<connect gate=".2" pin="PD12" pad="59"/>
<connect gate=".2" pin="PD13" pad="60"/>
<connect gate=".2" pin="PD14" pad="61"/>
<connect gate=".2" pin="PD15" pad="62"/>
<connect gate=".2" pin="PD2" pad="83"/>
<connect gate=".2" pin="PD3" pad="84"/>
<connect gate=".2" pin="PD4" pad="85"/>
<connect gate=".2" pin="PD5" pad="86"/>
<connect gate=".2" pin="PD6" pad="87"/>
<connect gate=".2" pin="PD7" pad="88"/>
<connect gate=".2" pin="PD8" pad="55"/>
<connect gate=".2" pin="PD9" pad="56"/>
<connect gate=".3" pin="BOOT0" pad="94"/>
<connect gate=".3" pin="NRST" pad="14"/>
<connect gate=".3" pin="PE0" pad="97"/>
<connect gate=".3" pin="PE1" pad="98"/>
<connect gate=".3" pin="PE10" pad="41"/>
<connect gate=".3" pin="PE11" pad="42"/>
<connect gate=".3" pin="PE12" pad="43"/>
<connect gate=".3" pin="PE13" pad="44"/>
<connect gate=".3" pin="PE14" pad="45"/>
<connect gate=".3" pin="PE15" pad="46"/>
<connect gate=".3" pin="PE2" pad="1"/>
<connect gate=".3" pin="PE3" pad="2"/>
<connect gate=".3" pin="PE4" pad="3"/>
<connect gate=".3" pin="PE5" pad="4"/>
<connect gate=".3" pin="PE6" pad="5"/>
<connect gate=".3" pin="PE7" pad="38"/>
<connect gate=".3" pin="PE8" pad="39"/>
<connect gate=".3" pin="PE9" pad="40"/>
<connect gate=".3" pin="PH0" pad="12"/>
<connect gate=".3" pin="PH1" pad="13"/>
<connect gate=".3" pin="VBAT" pad="6"/>
<connect gate=".3" pin="VCAP_1" pad="49"/>
<connect gate=".3" pin="VCAP_2" pad="73"/>
<connect gate=".3" pin="VDD" pad="11"/>
<connect gate=".3" pin="VDD@1" pad="19"/>
<connect gate=".3" pin="VDD@2" pad="28"/>
<connect gate=".3" pin="VDD@3" pad="50"/>
<connect gate=".3" pin="VDD@4" pad="75"/>
<connect gate=".3" pin="VDD@5" pad="100"/>
<connect gate=".3" pin="VDDA" pad="22"/>
<connect gate=".3" pin="VREF+" pad="21"/>
<connect gate=".3" pin="VSS" pad="10"/>
<connect gate=".3" pin="VSS@1" pad="27"/>
<connect gate=".3" pin="VSS@2" pad="74"/>
<connect gate=".3" pin="VSS@3" pad="99"/>
<connect gate=".3" pin="VSSA" pad="20"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X5" prefix="JP" uservalue="yes">
<gates>
<gate name="G$1" symbol="PINHD5" x="0" y="-5.08"/>
</gates>
<devices>
<device name="" package="1X05/90_FLAT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
<class number="1" name="power" width="0" drill="0">
</class>
</classes>
<parts>
<part name="D1" library="walkgeek-eagle" deviceset="NOKIA1100_DISP" device=""/>
<part name="SB1" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB2" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB3" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB4" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB5" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB6" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB7" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB8" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB9" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB10" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB11" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB12" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB13" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB14" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB15" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB16" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="SB17" library="walkgeek-eagle" deviceset="NOKIA1100_KEY_PAD_0" device=""/>
<part name="B1" library="walkgeek-eagle" deviceset="NOKIA1100_BATTERY_CONN" device=""/>
<part name="DD1" library="walkgeek-eagle" deviceset="CS43L22" device=""/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="C1" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C2" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C3" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C4" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C5" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C6" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C7" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C8" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C9" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C10" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="150pF"/>
<part name="C11" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="150pF"/>
<part name="C12" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C13" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="0.022uF"/>
<part name="C14" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="0.022uF"/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
<part name="X1" library="walkgeek-eagle" deviceset="NOKIA1100_EXT_CONN" device=""/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND6" library="supply1" deviceset="GND" device=""/>
<part name="GND7" library="supply1" deviceset="GND" device=""/>
<part name="GND8" library="supply1" deviceset="GND" device=""/>
<part name="GND9" library="supply1" deviceset="GND" device=""/>
<part name="R2" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="51"/>
<part name="R3" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="51"/>
<part name="R1" library="walkgeek-eagle" deviceset="R-EU_" device="R0402" value="10K"/>
<part name="GND11" library="supply1" deviceset="GND" device=""/>
<part name="R4" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="10K"/>
<part name="R6" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="1K"/>
<part name="+3V1" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="+3V2" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="+2V1" library="walkgeek-eagle" deviceset="+2V5" device=""/>
<part name="C15" library="walkgeek-eagle" deviceset="CPOL-EU" device="SMCA" value="1uF"/>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="GND12" library="supply1" deviceset="GND" device=""/>
<part name="VT1" library="walkgeek-eagle" deviceset="IRLML6402" device=""/>
<part name="R7" library="walkgeek-eagle" deviceset="R-EU_" device="R1206" value="33(*)"/>
<part name="VBAT1" library="walkgeek-eagle" deviceset="VBAT" device=""/>
<part name="C16" library="walkgeek-eagle" deviceset="C-EU" device="C0805" value="0.1uF"/>
<part name="GND13" library="supply1" deviceset="GND" device=""/>
<part name="+3V3" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="+3V6" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="GND10" library="supply1" deviceset="GND" device=""/>
<part name="GND14" library="supply1" deviceset="GND" device=""/>
<part name="X2" library="walkgeek-eagle" deviceset="MICROSD_CONN" device=""/>
<part name="GND16" library="supply1" deviceset="GND" device=""/>
<part name="R29" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="47K"/>
<part name="R30" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="47K"/>
<part name="R31" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="47K"/>
<part name="R32" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="47K"/>
<part name="R33" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="47K"/>
<part name="C18" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="GND18" library="supply1" deviceset="GND" device=""/>
<part name="+3V9" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="R34" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="47K"/>
<part name="DD3" library="walkgeek-eagle" deviceset="LTC4054ES5-4.2" device=""/>
<part name="R35" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="2K 1%"/>
<part name="GND17" library="supply1" deviceset="GND" device=""/>
<part name="GND20" library="supply1" deviceset="GND" device=""/>
<part name="GND22" library="supply1" deviceset="GND" device=""/>
<part name="R38" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="10K 1%"/>
<part name="R39" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="10K 1%"/>
<part name="GND23" library="supply1" deviceset="GND" device=""/>
<part name="C21" library="walkgeek-eagle" deviceset="C-EU" device="C0805" value="1uF"/>
<part name="GND25" library="supply1" deviceset="GND" device=""/>
<part name="R40" library="walkgeek-eagle" deviceset="R-EU_" device="R1206" value="1.8"/>
<part name="VT3" library="walkgeek-eagle" deviceset="IRLML6402" device=""/>
<part name="VBAT5" library="walkgeek-eagle" deviceset="VBAT" device=""/>
<part name="R41" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="10K"/>
<part name="GND26" library="supply1" deviceset="GND" device=""/>
<part name="VT4" library="walkgeek-eagle" deviceset="IRLML6402" device=""/>
<part name="R42" library="walkgeek-eagle" deviceset="R-EU_" device="R0805" value="10K"/>
<part name="VD1" library="walkgeek-eagle" deviceset="VD-SMA" device="" value="STTH1R02"/>
<part name="VD2" library="walkgeek-eagle" deviceset="VD-SMA" device="" value="STTH1R02"/>
<part name="VT5" library="walkgeek-eagle" deviceset="VT_NPN_DIGITAL" device="" value="BCR135"/>
<part name="VT6" library="walkgeek-eagle" deviceset="VT_NPN_DIGITAL" device="" value="BCR135"/>
<part name="GND27" library="supply1" deviceset="GND" device=""/>
<part name="VD3" library="walkgeek-eagle" deviceset="ESDA6V1W5" device=""/>
<part name="VD4" library="walkgeek-eagle" deviceset="ESDA6V1W5" device=""/>
<part name="+3V10" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="+3V11" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="VD5" library="walkgeek-eagle" deviceset="ESDA6V1W5" device=""/>
<part name="R5" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="0"/>
<part name="XT1" library="walkgeek-eagle" deviceset="USB_MINI_CONN" device="" value="5075BMR-05-SM"/>
<part name="GND28" library="supply1" deviceset="GND" device=""/>
<part name="C25" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="0.01uF"/>
<part name="GND40" library="supply1" deviceset="GND" device=""/>
<part name="DD4" library="walkgeek-eagle" deviceset="USBLC6-2SC6" device=""/>
<part name="C33" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="GND44" library="supply1" deviceset="GND" device=""/>
<part name="GND45" library="supply1" deviceset="GND" device=""/>
<part name="DD5" library="walkgeek-eagle" deviceset="LIS302DL" device=""/>
<part name="C35" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="+3V14" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="GND29" library="supply1" deviceset="GND" device=""/>
<part name="GND47" library="supply1" deviceset="GND" device=""/>
<part name="GND49" library="supply1" deviceset="GND" device=""/>
<part name="C36" library="walkgeek-eagle" deviceset="C-EU" device="C0805" value="100pF"/>
<part name="GND50" library="supply1" deviceset="GND" device=""/>
<part name="R51" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="4.7K"/>
<part name="R52" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="4.7K"/>
<part name="+3V16" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="DA1" library="walkgeek-eagle" deviceset="LD3985MXXR" device="" value="LD3985M25R"/>
<part name="VBAT3" library="walkgeek-eagle" deviceset="VBAT" device=""/>
<part name="C37" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C38" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="0.01uF"/>
<part name="C39" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C40" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C41" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="GND51" library="supply1" deviceset="GND" device=""/>
<part name="DA2" library="walkgeek-eagle" deviceset="LD3985MXXR" device="" value="LD3985M33R"/>
<part name="VBAT4" library="walkgeek-eagle" deviceset="VBAT" device=""/>
<part name="C42" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C43" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="0.01uF"/>
<part name="C44" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C45" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C46" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="GND52" library="supply1" deviceset="GND" device=""/>
<part name="+2V2" library="walkgeek-eagle" deviceset="+2V5" device=""/>
<part name="+3V17" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="+3V7" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="C47" library="walkgeek-eagle" deviceset="C-EU" device="C0805" value="0.01uF"/>
<part name="GND53" library="supply1" deviceset="GND" device=""/>
<part name="R55" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="100K"/>
<part name="C48" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="+3V18" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="GND56" library="supply1" deviceset="GND" device=""/>
<part name="C49" library="walkgeek-eagle" deviceset="CPOL-EU" device="SMCA" value="2.2uF"/>
<part name="C50" library="walkgeek-eagle" deviceset="CPOL-EU" device="SMCA" value="2.2uF"/>
<part name="GND57" library="supply1" deviceset="GND" device=""/>
<part name="GND58" library="supply1" deviceset="GND" device=""/>
<part name="C51" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C52" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C53" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C54" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C55" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C62" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="1uF"/>
<part name="C63" library="walkgeek-eagle" deviceset="CPOL-EU" device="SMCA" value="1uF"/>
<part name="C64" library="walkgeek-eagle" deviceset="CPOL-EU" device="SMCA" value="1uF"/>
<part name="C65" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="C66" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="GND61" library="supply1" deviceset="GND" device=""/>
<part name="GND62" library="supply1" deviceset="GND" device=""/>
<part name="+2V3" library="walkgeek-eagle" deviceset="+2V5" device=""/>
<part name="R57" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="47"/>
<part name="L1" library="walkgeek-eagle" deviceset="FCM1608" device="" value="FCM1608-0603"/>
<part name="GND60" library="supply1" deviceset="GND" device=""/>
<part name="ZQ2" library="walkgeek-eagle" deviceset="QUARTZ_5MM" device="" value="8MHz"/>
<part name="R59" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="220"/>
<part name="C68" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="20pF"/>
<part name="C69" library="walkgeek-eagle" deviceset="C-EU" device="C0603" value="20pF"/>
<part name="GND64" library="supply1" deviceset="GND" device=""/>
<part name="M1" library="walkgeek-eagle" deviceset="NOKIA1100_VIBRATOR" device=""/>
<part name="GND15" library="supply1" deviceset="GND" device=""/>
<part name="VT2" library="walkgeek-eagle" deviceset="IRLML6402" device=""/>
<part name="VBAT2" library="walkgeek-eagle" deviceset="VBAT" device=""/>
<part name="C17" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="GND30" library="supply1" deviceset="GND" device=""/>
<part name="R8" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="10K"/>
<part name="DD2" library="walkgeek-eagle" deviceset="STM32F4XXVXT" device=""/>
<part name="GND31" library="supply1" deviceset="GND" device=""/>
<part name="C22" library="walkgeek-eagle" deviceset="C-EU" device="C0402" value="0.1uF"/>
<part name="R9" library="walkgeek-eagle" deviceset="R-EU_" device="R0603" value="10K"/>
<part name="+3V4" library="walkgeek-eagle" deviceset="+3V3" device=""/>
<part name="JP1" library="walkgeek-eagle" deviceset="PINHD-1X5" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="716.28" y="223.52" size="1.778" layer="91">SWD</text>
</plain>
<instances>
<instance part="D1" gate="D$1" x="754.38" y="365.76"/>
<instance part="SB1" gate="G$1" x="746.76" y="307.34"/>
<instance part="SB2" gate="G$1" x="746.76" y="299.72"/>
<instance part="SB3" gate="G$1" x="787.4" y="307.34"/>
<instance part="SB4" gate="G$1" x="767.08" y="302.26"/>
<instance part="SB5" gate="G$1" x="787.4" y="299.72"/>
<instance part="SB6" gate="G$1" x="746.76" y="292.1"/>
<instance part="SB7" gate="G$1" x="767.08" y="292.1"/>
<instance part="SB8" gate="G$1" x="787.4" y="292.1"/>
<instance part="SB9" gate="G$1" x="746.76" y="284.48"/>
<instance part="SB10" gate="G$1" x="767.08" y="284.48"/>
<instance part="SB11" gate="G$1" x="787.4" y="284.48"/>
<instance part="SB12" gate="G$1" x="746.76" y="276.86"/>
<instance part="SB13" gate="G$1" x="767.08" y="276.86"/>
<instance part="SB14" gate="G$1" x="787.4" y="276.86"/>
<instance part="SB15" gate="G$1" x="746.76" y="269.24"/>
<instance part="SB16" gate="G$1" x="767.08" y="269.24"/>
<instance part="SB17" gate="G$1" x="787.4" y="269.24"/>
<instance part="B1" gate="B$1" x="505.46" y="215.9"/>
<instance part="DD1" gate="DD$1" x="543.56" y="347.98"/>
<instance part="GND1" gate="1" x="546.1" y="340.36" smashed="yes"/>
<instance part="C1" gate="G$1" x="454.66" y="299.72"/>
<instance part="C2" gate="G$1" x="464.82" y="299.72"/>
<instance part="C3" gate="G$1" x="474.98" y="299.72"/>
<instance part="C4" gate="G$1" x="490.22" y="284.48"/>
<instance part="C5" gate="G$1" x="548.64" y="307.34"/>
<instance part="C6" gate="G$1" x="561.34" y="307.34"/>
<instance part="C7" gate="G$1" x="485.14" y="317.5"/>
<instance part="C8" gate="G$1" x="492.76" y="317.5"/>
<instance part="C9" gate="G$1" x="551.18" y="284.48"/>
<instance part="C10" gate="G$1" x="561.34" y="287.02"/>
<instance part="C11" gate="G$1" x="571.5" y="289.56"/>
<instance part="C12" gate="G$1" x="581.66" y="292.1"/>
<instance part="C13" gate="G$1" x="553.72" y="340.36"/>
<instance part="C14" gate="G$1" x="568.96" y="340.36"/>
<instance part="GND2" gate="1" x="551.18" y="274.32" smashed="yes"/>
<instance part="X1" gate="X$1" x="596.9" y="342.9" rot="MR0"/>
<instance part="GND4" gate="1" x="485.14" y="309.88" smashed="yes"/>
<instance part="GND5" gate="1" x="490.22" y="276.86" smashed="yes"/>
<instance part="GND6" gate="1" x="500.38" y="276.86" smashed="yes"/>
<instance part="GND7" gate="1" x="454.66" y="276.86" smashed="yes"/>
<instance part="GND8" gate="1" x="482.6" y="340.36" smashed="yes"/>
<instance part="GND9" gate="1" x="474.98" y="309.88" smashed="yes"/>
<instance part="R2" gate="G$1" x="553.72" y="330.2" smashed="yes" rot="R90">
<attribute name="NAME" x="556.26" y="330.4286" size="1.778" layer="95"/>
<attribute name="VALUE" x="556.26" y="329.692" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R3" gate="G$1" x="568.96" y="330.2" smashed="yes" rot="R90">
<attribute name="NAME" x="571.5" y="330.4286" size="1.778" layer="95"/>
<attribute name="VALUE" x="571.5" y="329.692" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R1" gate="G$1" x="474.98" y="317.5" smashed="yes" rot="R90">
<attribute name="NAME" x="477.52" y="318.9986" size="1.778" layer="95"/>
<attribute name="VALUE" x="477.52" y="315.722" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="GND11" gate="1" x="561.34" y="297.18" smashed="yes"/>
<instance part="R4" gate="G$1" x="581.66" y="314.96"/>
<instance part="R6" gate="G$1" x="601.98" y="284.48" smashed="yes" rot="R90">
<attribute name="NAME" x="604.52" y="284.7086" size="1.778" layer="95"/>
<attribute name="VALUE" x="604.52" y="283.972" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="+3V1" gate="G$1" x="548.64" y="330.2"/>
<instance part="+3V2" gate="G$1" x="497.84" y="292.1"/>
<instance part="+2V1" gate="G$1" x="454.66" y="307.34"/>
<instance part="C15" gate="G$1" x="487.68" y="299.72"/>
<instance part="GND3" gate="1" x="762" y="264.16" smashed="yes"/>
<instance part="GND12" gate="1" x="756.92" y="330.2" smashed="yes"/>
<instance part="VT1" gate="VT$1" x="792.48" y="335.28" rot="MR0"/>
<instance part="R7" gate="G$1" x="777.24" y="330.2"/>
<instance part="VBAT1" gate="G$1" x="789.94" y="347.98"/>
<instance part="C16" gate="G$1" x="777.24" y="350.52"/>
<instance part="GND13" gate="1" x="777.24" y="342.9" smashed="yes"/>
<instance part="+3V3" gate="G$1" x="777.24" y="355.6"/>
<instance part="+3V6" gate="G$1" x="574.04" y="317.5"/>
<instance part="GND10" gate="1" x="553.72" y="322.58" smashed="yes"/>
<instance part="GND14" gate="1" x="614.68" y="307.34" smashed="yes"/>
<instance part="X2" gate="X$1" x="675.64" y="347.98"/>
<instance part="GND16" gate="1" x="680.72" y="314.96" smashed="yes"/>
<instance part="R29" gate="G$1" x="683.26" y="353.06" smashed="yes" rot="R90">
<attribute name="NAME" x="685.038" y="353.5426" size="1.778" layer="95"/>
<attribute name="VALUE" x="685.038" y="352.552" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R30" gate="G$1" x="690.88" y="360.68" smashed="yes" rot="R90">
<attribute name="NAME" x="692.658" y="361.1626" size="1.778" layer="95"/>
<attribute name="VALUE" x="692.658" y="360.172" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R31" gate="G$1" x="698.5" y="353.06" smashed="yes" rot="R90">
<attribute name="NAME" x="700.278" y="353.5426" size="1.778" layer="95"/>
<attribute name="VALUE" x="700.278" y="352.552" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R32" gate="G$1" x="706.12" y="360.68" smashed="yes" rot="R90">
<attribute name="NAME" x="707.898" y="361.1626" size="1.778" layer="95"/>
<attribute name="VALUE" x="707.898" y="360.172" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R33" gate="G$1" x="713.74" y="353.06" smashed="yes" rot="R90">
<attribute name="NAME" x="715.518" y="353.5426" size="1.778" layer="95"/>
<attribute name="VALUE" x="715.518" y="352.552" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="C18" gate="G$1" x="668.02" y="360.68"/>
<instance part="GND18" gate="1" x="668.02" y="353.06" smashed="yes"/>
<instance part="+3V9" gate="G$1" x="683.26" y="368.3"/>
<instance part="R34" gate="G$1" x="688.34" y="327.66"/>
<instance part="DD3" gate="G$1" x="482.6" y="238.76"/>
<instance part="R35" gate="G$1" x="490.22" y="208.28" smashed="yes" rot="MR90">
<attribute name="NAME" x="488.442" y="208.7626" size="1.778" layer="95" rot="MR0"/>
<attribute name="VALUE" x="488.442" y="207.772" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND17" gate="1" x="490.22" y="200.66" smashed="yes" rot="MR0"/>
<instance part="GND20" gate="1" x="477.52" y="226.06" smashed="yes"/>
<instance part="GND22" gate="1" x="508" y="200.66" smashed="yes"/>
<instance part="R38" gate="G$1" x="530.86" y="208.28" smashed="yes" rot="R90">
<attribute name="NAME" x="532.638" y="208.7626" size="1.778" layer="95"/>
<attribute name="VALUE" x="532.638" y="207.772" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R39" gate="G$1" x="518.16" y="215.9"/>
<instance part="GND23" gate="1" x="530.86" y="200.66" smashed="yes"/>
<instance part="C21" gate="G$1" x="467.36" y="233.68"/>
<instance part="GND25" gate="1" x="467.36" y="226.06" smashed="yes"/>
<instance part="R40" gate="G$1" x="462.28" y="238.76"/>
<instance part="VT3" gate="VT$1" x="513.08" y="241.3" smashed="yes" rot="R270">
<attribute name="NAME" x="513.08" y="246.38" size="1.778" layer="95" rot="MR0"/>
<attribute name="VALUE" x="513.08" y="243.84" size="1.778" layer="96" rot="MR0"/>
</instance>
<instance part="VBAT5" gate="G$1" x="553.72" y="251.46"/>
<instance part="R41" gate="G$1" x="452.12" y="231.14" smashed="yes" rot="R90">
<attribute name="NAME" x="453.898" y="231.6226" size="1.778" layer="95"/>
<attribute name="VALUE" x="453.898" y="230.632" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="GND26" gate="1" x="452.12" y="223.52" smashed="yes"/>
<instance part="VT4" gate="VT$1" x="543.56" y="246.38" smashed="yes" rot="R90">
<attribute name="NAME" x="548.64" y="246.38" size="1.778" layer="95"/>
<attribute name="VALUE" x="548.64" y="243.84" size="1.778" layer="96"/>
</instance>
<instance part="R42" gate="G$1" x="530.86" y="243.84" smashed="yes" rot="R90">
<attribute name="NAME" x="532.638" y="244.3226" size="1.778" layer="95"/>
<attribute name="VALUE" x="532.638" y="243.332" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="VD1" gate="G$1" x="520.7" y="248.92" smashed="yes">
<attribute name="NAME" x="518.16" y="254.4826" size="1.778" layer="95"/>
<attribute name="VALUE" x="515.62" y="251.6886" size="1.778" layer="96"/>
</instance>
<instance part="VD2" gate="G$1" x="546.1" y="238.76" smashed="yes">
<attribute name="NAME" x="543.56" y="234.1626" size="1.778" layer="95"/>
<attribute name="VALUE" x="543.56" y="231.3686" size="1.778" layer="96"/>
</instance>
<instance part="VT5" gate="G$1" x="528.32" y="226.06" smashed="yes">
<attribute name="NAME" x="525.78" y="223.52" size="1.778" layer="95" rot="MR0"/>
<attribute name="VALUE" x="525.78" y="220.98" size="1.778" layer="96" rot="MR0"/>
</instance>
<instance part="VT6" gate="G$1" x="538.48" y="226.06" smashed="yes" rot="MR0">
<attribute name="NAME" x="541.02" y="223.52" size="1.778" layer="95"/>
<attribute name="VALUE" x="541.02" y="220.98" size="1.778" layer="96"/>
</instance>
<instance part="GND27" gate="1" x="533.4" y="218.44" smashed="yes"/>
<instance part="VD3" gate="G$1" x="563.88" y="363.22"/>
<instance part="VD4" gate="G$1" x="591.82" y="363.22"/>
<instance part="+3V10" gate="G$1" x="581.66" y="381"/>
<instance part="+3V11" gate="G$1" x="609.6" y="381"/>
<instance part="VD5" gate="G$1" x="607.06" y="309.88" rot="MR0"/>
<instance part="R5" gate="G$1" x="586.74" y="330.2"/>
<instance part="XT1" gate="G$1" x="759.46" y="231.14"/>
<instance part="GND28" gate="1" x="762" y="210.82" smashed="yes"/>
<instance part="C25" gate="G$1" x="754.38" y="246.38"/>
<instance part="GND40" gate="1" x="754.38" y="238.76" smashed="yes"/>
<instance part="DD4" gate="DD$1" x="777.24" y="228.6" rot="MR0"/>
<instance part="C33" gate="G$1" x="767.08" y="218.44"/>
<instance part="GND44" gate="1" x="767.08" y="210.82" smashed="yes" rot="MR0"/>
<instance part="GND45" gate="1" x="802.64" y="218.44" smashed="yes" rot="MR0"/>
<instance part="DD5" gate="G$1" x="683.26" y="299.72"/>
<instance part="C35" gate="G$1" x="673.1" y="276.86"/>
<instance part="+3V14" gate="G$1" x="673.1" y="299.72"/>
<instance part="GND29" gate="1" x="673.1" y="269.24" smashed="yes"/>
<instance part="GND47" gate="1" x="721.36" y="276.86" smashed="yes"/>
<instance part="GND49" gate="1" x="706.12" y="224.79" smashed="yes" rot="MR0"/>
<instance part="C36" gate="G$1" x="703.58" y="246.38"/>
<instance part="GND50" gate="1" x="695.96" y="246.38" smashed="yes" rot="MR0"/>
<instance part="R51" gate="G$1" x="500.38" y="355.6" smashed="yes" rot="R90">
<attribute name="NAME" x="502.158" y="356.0826" size="1.778" layer="95"/>
<attribute name="VALUE" x="502.158" y="355.092" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="R52" gate="G$1" x="490.22" y="355.6" smashed="yes" rot="R90">
<attribute name="NAME" x="491.998" y="356.0826" size="1.778" layer="95"/>
<attribute name="VALUE" x="491.998" y="355.092" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="+3V16" gate="G$1" x="495.3" y="363.22"/>
<instance part="DA1" gate="G$1" x="596.9" y="248.92"/>
<instance part="VBAT3" gate="G$1" x="574.04" y="251.46"/>
<instance part="C37" gate="G$1" x="574.04" y="241.3"/>
<instance part="C38" gate="G$1" x="622.3" y="241.3"/>
<instance part="C39" gate="G$1" x="635" y="241.3"/>
<instance part="C40" gate="G$1" x="584.2" y="241.3"/>
<instance part="C41" gate="G$1" x="645.16" y="241.3"/>
<instance part="GND51" gate="1" x="607.06" y="231.14" smashed="yes" rot="MR0"/>
<instance part="DA2" gate="G$1" x="596.9" y="215.9"/>
<instance part="VBAT4" gate="G$1" x="574.04" y="218.44"/>
<instance part="C42" gate="G$1" x="574.04" y="208.28"/>
<instance part="C43" gate="G$1" x="622.3" y="208.28"/>
<instance part="C44" gate="G$1" x="635" y="208.28"/>
<instance part="C45" gate="G$1" x="584.2" y="208.28"/>
<instance part="C46" gate="G$1" x="645.16" y="208.28"/>
<instance part="GND52" gate="1" x="607.06" y="198.12" smashed="yes" rot="MR0"/>
<instance part="+2V2" gate="G$1" x="645.16" y="251.46"/>
<instance part="+3V17" gate="G$1" x="645.16" y="218.44"/>
<instance part="+3V7" gate="G$1" x="668.02" y="368.3"/>
<instance part="C47" gate="G$1" x="589.28" y="284.48"/>
<instance part="GND53" gate="1" x="589.28" y="276.86" smashed="yes"/>
<instance part="R55" gate="G$1" x="571.5" y="119.38" smashed="yes" rot="R90">
<attribute name="NAME" x="573.278" y="119.8626" size="1.778" layer="95"/>
<attribute name="VALUE" x="573.278" y="118.872" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="C48" gate="G$1" x="571.5" y="109.22"/>
<instance part="+3V18" gate="G$1" x="571.5" y="127"/>
<instance part="GND56" gate="1" x="571.5" y="101.6" smashed="yes" rot="MR0"/>
<instance part="C49" gate="G$1" x="624.84" y="99.06"/>
<instance part="C50" gate="G$1" x="635" y="101.6"/>
<instance part="GND57" gate="1" x="624.84" y="91.44" smashed="yes" rot="MR0"/>
<instance part="GND58" gate="1" x="635" y="91.44" smashed="yes" rot="MR0"/>
<instance part="C51" gate="G$1" x="640.08" y="144.78"/>
<instance part="C52" gate="G$1" x="650.24" y="144.78"/>
<instance part="C53" gate="G$1" x="660.4" y="144.78"/>
<instance part="C54" gate="G$1" x="670.56" y="144.78"/>
<instance part="C55" gate="G$1" x="680.72" y="144.78"/>
<instance part="C62" gate="G$1" x="629.92" y="144.78"/>
<instance part="C63" gate="G$1" x="652.78" y="119.38"/>
<instance part="C64" gate="G$1" x="650.24" y="101.6"/>
<instance part="C65" gate="G$1" x="660.4" y="119.38"/>
<instance part="C66" gate="G$1" x="660.4" y="101.6"/>
<instance part="GND61" gate="1" x="660.4" y="109.22" smashed="yes" rot="MR0"/>
<instance part="GND62" gate="1" x="660.4" y="91.44" smashed="yes" rot="MR0"/>
<instance part="+2V3" gate="G$1" x="675.64" y="127"/>
<instance part="R57" gate="G$1" x="665.48" y="127"/>
<instance part="L1" gate="G$1" x="675.64" y="121.92" smashed="yes" rot="MR270">
<attribute name="NAME" x="678.18" y="116.84" size="1.778" layer="95" rot="MR270"/>
<attribute name="VALUE" x="680.72" y="124.46" size="1.778" layer="96" rot="R270" align="top-left"/>
</instance>
<instance part="GND60" gate="1" x="640.08" y="134.62" smashed="yes" rot="MR0"/>
<instance part="ZQ2" gate="G$1" x="640.08" y="162.56"/>
<instance part="R59" gate="G$1" x="635" y="157.48"/>
<instance part="C68" gate="G$1" x="652.78" y="157.48" smashed="yes" rot="R90">
<attribute name="NAME" x="656.844" y="162.941" size="1.778" layer="95"/>
<attribute name="VALUE" x="656.844" y="160.401" size="1.778" layer="96"/>
</instance>
<instance part="C69" gate="G$1" x="652.78" y="170.18" smashed="yes" rot="R90">
<attribute name="NAME" x="656.844" y="175.641" size="1.778" layer="95"/>
<attribute name="VALUE" x="656.844" y="174.879" size="1.778" layer="96" rot="MR180"/>
</instance>
<instance part="GND64" gate="1" x="665.48" y="154.94" smashed="yes" rot="MR0"/>
<instance part="M1" gate="M$1" x="759.46" y="170.18" rot="MR0"/>
<instance part="GND15" gate="1" x="759.46" y="157.48" smashed="yes"/>
<instance part="VT2" gate="VT$1" x="762" y="177.8" smashed="yes" rot="MR0">
<attribute name="NAME" x="767.08" y="175.26" size="1.778" layer="95"/>
<attribute name="VALUE" x="767.08" y="172.72" size="1.778" layer="96"/>
</instance>
<instance part="VBAT2" gate="G$1" x="759.46" y="187.96"/>
<instance part="C17" gate="G$1" x="746.76" y="180.34"/>
<instance part="GND30" gate="1" x="746.76" y="172.72" smashed="yes"/>
<instance part="R8" gate="G$1" x="767.08" y="185.42"/>
<instance part="DD2" gate=".1" x="508" y="170.18"/>
<instance part="DD2" gate=".2" x="510.54" y="114.3"/>
<instance part="DD2" gate=".3" x="586.74" y="170.18"/>
<instance part="GND31" gate="1" x="584.2" y="101.6" smashed="yes" rot="MR0"/>
<instance part="C22" gate="G$1" x="690.88" y="144.78"/>
<instance part="R9" gate="G$1" x="797.56" y="342.9"/>
<instance part="+3V4" gate="G$1" x="690.88" y="152.4"/>
<instance part="JP1" gate="G$1" x="718.82" y="233.68"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="1">
<segment>
<pinref part="DD1" gate="DD$1" pin="SPKR/HP"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="543.56" y1="342.9" x2="546.1" y2="342.9" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C9" gate="G$1" pin="2"/>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="551.18" y1="279.4" x2="551.18" y2="276.86" width="0.1524" layer="91"/>
<pinref part="C10" gate="G$1" pin="2"/>
<wire x1="561.34" y1="281.94" x2="561.34" y2="276.86" width="0.1524" layer="91"/>
<wire x1="561.34" y1="276.86" x2="551.18" y2="276.86" width="0.1524" layer="91"/>
<junction x="551.18" y="276.86"/>
<pinref part="C11" gate="G$1" pin="2"/>
<wire x1="571.5" y1="284.48" x2="571.5" y2="276.86" width="0.1524" layer="91"/>
<wire x1="571.5" y1="276.86" x2="561.34" y2="276.86" width="0.1524" layer="91"/>
<junction x="561.34" y="276.86"/>
<pinref part="C12" gate="G$1" pin="2"/>
<wire x1="581.66" y1="287.02" x2="581.66" y2="276.86" width="0.1524" layer="91"/>
<wire x1="581.66" y1="276.86" x2="571.5" y2="276.86" width="0.1524" layer="91"/>
<junction x="571.5" y="276.86"/>
<pinref part="DD1" gate="DD$1" pin="AGND"/>
<wire x1="543.56" y1="284.48" x2="546.1" y2="284.48" width="0.1524" layer="91"/>
<wire x1="546.1" y1="284.48" x2="546.1" y2="276.86" width="0.1524" layer="91"/>
<wire x1="546.1" y1="276.86" x2="551.18" y2="276.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C7" gate="G$1" pin="2"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C4" gate="G$1" pin="2"/>
<pinref part="GND5" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="DD1" gate="DD$1" pin="DGND"/>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="502.92" y1="287.02" x2="500.38" y2="287.02" width="0.1524" layer="91"/>
<wire x1="500.38" y1="287.02" x2="500.38" y2="284.48" width="0.1524" layer="91"/>
<pinref part="DD1" gate="DD$1" pin="GND/PAD"/>
<wire x1="500.38" y1="284.48" x2="500.38" y2="279.4" width="0.1524" layer="91"/>
<wire x1="502.92" y1="284.48" x2="500.38" y2="284.48" width="0.1524" layer="91"/>
<junction x="500.38" y="284.48"/>
</segment>
<segment>
<pinref part="C3" gate="G$1" pin="2"/>
<wire x1="474.98" y1="294.64" x2="474.98" y2="292.1" width="0.1524" layer="91"/>
<wire x1="474.98" y1="292.1" x2="464.82" y2="292.1" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="2"/>
<wire x1="464.82" y1="292.1" x2="454.66" y2="292.1" width="0.1524" layer="91"/>
<wire x1="454.66" y1="292.1" x2="454.66" y2="294.64" width="0.1524" layer="91"/>
<pinref part="C2" gate="G$1" pin="2"/>
<wire x1="464.82" y1="294.64" x2="464.82" y2="292.1" width="0.1524" layer="91"/>
<junction x="464.82" y="292.1"/>
<wire x1="454.66" y1="292.1" x2="454.66" y2="279.4" width="0.1524" layer="91"/>
<junction x="454.66" y="292.1"/>
<pinref part="GND7" gate="1" pin="GND"/>
<wire x1="474.98" y1="292.1" x2="487.68" y2="292.1" width="0.1524" layer="91"/>
<junction x="474.98" y="292.1"/>
<pinref part="C15" gate="G$1" pin="-"/>
<wire x1="487.68" y1="292.1" x2="487.68" y2="294.64" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD1" gate="DD$1" pin="AD0"/>
<pinref part="GND8" gate="1" pin="GND"/>
<wire x1="502.92" y1="342.9" x2="482.6" y2="342.9" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND9" gate="1" pin="GND"/>
<pinref part="R1" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="C5" gate="G$1" pin="2"/>
<wire x1="548.64" y1="302.26" x2="548.64" y2="299.72" width="0.1524" layer="91"/>
<wire x1="548.64" y1="299.72" x2="561.34" y2="299.72" width="0.1524" layer="91"/>
<pinref part="C6" gate="G$1" pin="2"/>
<wire x1="561.34" y1="299.72" x2="561.34" y2="302.26" width="0.1524" layer="91"/>
<pinref part="GND11" gate="1" pin="GND"/>
<junction x="561.34" y="299.72"/>
</segment>
<segment>
<wire x1="741.68" y1="266.7" x2="762" y2="266.7" width="0.1524" layer="91"/>
<wire x1="782.32" y1="266.7" x2="762" y2="266.7" width="0.1524" layer="91"/>
<junction x="762" y="266.7"/>
<pinref part="GND3" gate="1" pin="GND"/>
<pinref part="SB1" gate="G$1" pin="OUTER"/>
<pinref part="SB2" gate="G$1" pin="OUTER"/>
<wire x1="741.68" y1="307.34" x2="741.68" y2="299.72" width="0.1524" layer="91"/>
<pinref part="SB6" gate="G$1" pin="OUTER"/>
<wire x1="741.68" y1="299.72" x2="741.68" y2="292.1" width="0.1524" layer="91"/>
<junction x="741.68" y="299.72"/>
<pinref part="SB9" gate="G$1" pin="OUTER"/>
<wire x1="741.68" y1="292.1" x2="741.68" y2="284.48" width="0.1524" layer="91"/>
<junction x="741.68" y="292.1"/>
<pinref part="SB12" gate="G$1" pin="OUTER"/>
<wire x1="741.68" y1="284.48" x2="741.68" y2="276.86" width="0.1524" layer="91"/>
<junction x="741.68" y="284.48"/>
<pinref part="SB15" gate="G$1" pin="OUTER"/>
<wire x1="741.68" y1="276.86" x2="741.68" y2="269.24" width="0.1524" layer="91"/>
<junction x="741.68" y="276.86"/>
<wire x1="741.68" y1="269.24" x2="741.68" y2="266.7" width="0.1524" layer="91"/>
<junction x="741.68" y="269.24"/>
<pinref part="SB16" gate="G$1" pin="OUTER"/>
<wire x1="762" y1="266.7" x2="762" y2="269.24" width="0.1524" layer="91"/>
<pinref part="SB13" gate="G$1" pin="OUTER"/>
<wire x1="762" y1="269.24" x2="762" y2="276.86" width="0.1524" layer="91"/>
<junction x="762" y="269.24"/>
<pinref part="SB10" gate="G$1" pin="OUTER"/>
<wire x1="762" y1="276.86" x2="762" y2="284.48" width="0.1524" layer="91"/>
<junction x="762" y="276.86"/>
<pinref part="SB7" gate="G$1" pin="OUTER"/>
<wire x1="762" y1="284.48" x2="762" y2="292.1" width="0.1524" layer="91"/>
<junction x="762" y="284.48"/>
<pinref part="SB4" gate="G$1" pin="OUTER"/>
<wire x1="762" y1="292.1" x2="762" y2="302.26" width="0.1524" layer="91"/>
<junction x="762" y="292.1"/>
<pinref part="SB17" gate="G$1" pin="OUTER"/>
<wire x1="782.32" y1="266.7" x2="782.32" y2="269.24" width="0.1524" layer="91"/>
<pinref part="SB14" gate="G$1" pin="OUTER"/>
<wire x1="782.32" y1="269.24" x2="782.32" y2="276.86" width="0.1524" layer="91"/>
<junction x="782.32" y="269.24"/>
<pinref part="SB11" gate="G$1" pin="OUTER"/>
<wire x1="782.32" y1="276.86" x2="782.32" y2="284.48" width="0.1524" layer="91"/>
<junction x="782.32" y="276.86"/>
<pinref part="SB8" gate="G$1" pin="OUTER"/>
<wire x1="782.32" y1="284.48" x2="782.32" y2="292.1" width="0.1524" layer="91"/>
<junction x="782.32" y="284.48"/>
<pinref part="SB5" gate="G$1" pin="OUTER"/>
<wire x1="782.32" y1="292.1" x2="782.32" y2="299.72" width="0.1524" layer="91"/>
<junction x="782.32" y="292.1"/>
<pinref part="SB3" gate="G$1" pin="OUTER"/>
<wire x1="782.32" y1="299.72" x2="782.32" y2="307.34" width="0.1524" layer="91"/>
<junction x="782.32" y="299.72"/>
</segment>
<segment>
<pinref part="D1" gate="D$1" pin="VSS"/>
<pinref part="GND12" gate="1" pin="GND"/>
<wire x1="756.92" y1="347.98" x2="756.92" y2="332.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C16" gate="G$1" pin="2"/>
<pinref part="GND13" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<wire x1="568.96" y1="325.12" x2="553.72" y2="325.12" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="1"/>
<junction x="568.96" y="325.12"/>
<wire x1="579.12" y1="325.12" x2="568.96" y2="325.12" width="0.1524" layer="91"/>
<pinref part="GND10" gate="1" pin="GND"/>
<junction x="553.72" y="325.12"/>
<wire x1="579.12" y1="325.12" x2="579.12" y2="330.2" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="1"/>
<wire x1="579.12" y1="330.2" x2="581.66" y2="330.2" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C18" gate="G$1" pin="2"/>
<pinref part="GND18" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="X2" gate="X$1" pin="VSS"/>
<pinref part="GND16" gate="1" pin="GND"/>
<wire x1="678.18" y1="330.2" x2="680.72" y2="330.2" width="0.1524" layer="91"/>
<wire x1="680.72" y1="330.2" x2="680.72" y2="327.66" width="0.1524" layer="91"/>
<pinref part="X2" gate="X$1" pin="SH"/>
<wire x1="680.72" y1="327.66" x2="680.72" y2="320.04" width="0.1524" layer="91"/>
<wire x1="680.72" y1="320.04" x2="680.72" y2="317.5" width="0.1524" layer="91"/>
<wire x1="678.18" y1="320.04" x2="680.72" y2="320.04" width="0.1524" layer="91"/>
<junction x="680.72" y="320.04"/>
<pinref part="R34" gate="G$1" pin="1"/>
<wire x1="683.26" y1="327.66" x2="680.72" y2="327.66" width="0.1524" layer="91"/>
<junction x="680.72" y="327.66"/>
</segment>
<segment>
<pinref part="DD3" gate="G$1" pin="GND"/>
<wire x1="480.06" y1="233.68" x2="477.52" y2="233.68" width="0.1524" layer="91"/>
<pinref part="GND20" gate="1" pin="GND"/>
<wire x1="477.52" y1="233.68" x2="477.52" y2="228.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R35" gate="G$1" pin="1"/>
<pinref part="GND17" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="B1" gate="B$1" pin="-"/>
<wire x1="505.46" y1="210.82" x2="508" y2="210.82" width="0.1524" layer="91"/>
<pinref part="GND22" gate="1" pin="GND"/>
<wire x1="508" y1="210.82" x2="508" y2="203.2" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R38" gate="G$1" pin="1"/>
<pinref part="GND23" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C21" gate="G$1" pin="2"/>
<pinref part="GND25" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="R41" gate="G$1" pin="1"/>
<pinref part="GND26" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="VT5" gate="G$1" pin="E"/>
<pinref part="VT6" gate="G$1" pin="E"/>
<wire x1="530.86" y1="220.98" x2="533.4" y2="220.98" width="0.1524" layer="91"/>
<pinref part="GND27" gate="1" pin="GND"/>
<wire x1="533.4" y1="220.98" x2="535.94" y2="220.98" width="0.1524" layer="91"/>
<junction x="533.4" y="220.98"/>
</segment>
<segment>
<pinref part="VD5" gate="G$1" pin="P$2"/>
<pinref part="GND14" gate="1" pin="GND"/>
<wire x1="614.68" y1="309.88" x2="612.14" y2="309.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C25" gate="G$1" pin="2"/>
<pinref part="GND40" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C33" gate="G$1" pin="2"/>
<pinref part="GND44" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="DD4" gate="DD$1" pin="GND"/>
<pinref part="GND45" gate="1" pin="GND"/>
<wire x1="800.1" y1="226.06" x2="802.64" y2="226.06" width="0.1524" layer="91"/>
<wire x1="802.64" y1="226.06" x2="802.64" y2="220.98" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="XT1" gate="G$1" pin="SH"/>
<pinref part="XT1" gate="G$1" pin="GND"/>
<wire x1="762" y1="218.44" x2="762" y2="220.98" width="0.1524" layer="91"/>
<wire x1="762" y1="218.44" x2="762" y2="213.36" width="0.1524" layer="91"/>
<junction x="762" y="218.44"/>
<pinref part="GND28" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C35" gate="G$1" pin="2"/>
<pinref part="GND29" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="DD5" gate="G$1" pin="GND@3"/>
<wire x1="718.82" y1="292.1" x2="721.36" y2="292.1" width="0.1524" layer="91"/>
<pinref part="GND47" gate="1" pin="GND"/>
<wire x1="721.36" y1="292.1" x2="721.36" y2="289.56" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="RESERVED@1"/>
<wire x1="721.36" y1="289.56" x2="721.36" y2="287.02" width="0.1524" layer="91"/>
<wire x1="721.36" y1="287.02" x2="721.36" y2="284.48" width="0.1524" layer="91"/>
<wire x1="721.36" y1="284.48" x2="721.36" y2="281.94" width="0.1524" layer="91"/>
<wire x1="721.36" y1="281.94" x2="721.36" y2="279.4" width="0.1524" layer="91"/>
<wire x1="718.82" y1="281.94" x2="721.36" y2="281.94" width="0.1524" layer="91"/>
<junction x="721.36" y="281.94"/>
<pinref part="DD5" gate="G$1" pin="GND"/>
<wire x1="718.82" y1="284.48" x2="721.36" y2="284.48" width="0.1524" layer="91"/>
<junction x="721.36" y="284.48"/>
<pinref part="DD5" gate="G$1" pin="GND@1"/>
<wire x1="718.82" y1="287.02" x2="721.36" y2="287.02" width="0.1524" layer="91"/>
<junction x="721.36" y="287.02"/>
<pinref part="DD5" gate="G$1" pin="GND@2"/>
<wire x1="718.82" y1="289.56" x2="721.36" y2="289.56" width="0.1524" layer="91"/>
<junction x="721.36" y="289.56"/>
<pinref part="DD5" gate="G$1" pin="SDO"/>
<wire x1="718.82" y1="294.64" x2="721.36" y2="294.64" width="0.1524" layer="91"/>
<wire x1="721.36" y1="294.64" x2="721.36" y2="292.1" width="0.1524" layer="91"/>
<junction x="721.36" y="292.1"/>
</segment>
<segment>
<pinref part="GND49" gate="1" pin="GND"/>
<wire x1="718.82" y1="236.22" x2="706.12" y2="236.22" width="0.1524" layer="91"/>
<wire x1="706.12" y1="236.22" x2="706.12" y2="227.33" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="C36" gate="G$1" pin="1"/>
<pinref part="GND50" gate="1" pin="GND"/>
<wire x1="695.96" y1="248.92" x2="703.58" y2="248.92" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DA1" gate="G$1" pin="GND"/>
<wire x1="594.36" y1="243.84" x2="594.36" y2="233.68" width="0.1524" layer="91"/>
<pinref part="GND51" gate="1" pin="GND"/>
<wire x1="594.36" y1="233.68" x2="607.06" y2="233.68" width="0.1524" layer="91"/>
<pinref part="C40" gate="G$1" pin="2"/>
<wire x1="584.2" y1="236.22" x2="584.2" y2="233.68" width="0.1524" layer="91"/>
<wire x1="584.2" y1="233.68" x2="594.36" y2="233.68" width="0.1524" layer="91"/>
<junction x="594.36" y="233.68"/>
<pinref part="C37" gate="G$1" pin="2"/>
<wire x1="574.04" y1="236.22" x2="574.04" y2="233.68" width="0.1524" layer="91"/>
<wire x1="574.04" y1="233.68" x2="584.2" y2="233.68" width="0.1524" layer="91"/>
<junction x="584.2" y="233.68"/>
<pinref part="C38" gate="G$1" pin="2"/>
<wire x1="622.3" y1="236.22" x2="622.3" y2="233.68" width="0.1524" layer="91"/>
<wire x1="622.3" y1="233.68" x2="607.06" y2="233.68" width="0.1524" layer="91"/>
<junction x="607.06" y="233.68"/>
<pinref part="C39" gate="G$1" pin="2"/>
<wire x1="635" y1="236.22" x2="635" y2="233.68" width="0.1524" layer="91"/>
<wire x1="635" y1="233.68" x2="622.3" y2="233.68" width="0.1524" layer="91"/>
<junction x="622.3" y="233.68"/>
<pinref part="C41" gate="G$1" pin="2"/>
<wire x1="645.16" y1="236.22" x2="645.16" y2="233.68" width="0.1524" layer="91"/>
<wire x1="645.16" y1="233.68" x2="635" y2="233.68" width="0.1524" layer="91"/>
<junction x="635" y="233.68"/>
</segment>
<segment>
<pinref part="DA2" gate="G$1" pin="GND"/>
<wire x1="594.36" y1="210.82" x2="594.36" y2="200.66" width="0.1524" layer="91"/>
<pinref part="GND52" gate="1" pin="GND"/>
<wire x1="594.36" y1="200.66" x2="607.06" y2="200.66" width="0.1524" layer="91"/>
<pinref part="C45" gate="G$1" pin="2"/>
<wire x1="584.2" y1="203.2" x2="584.2" y2="200.66" width="0.1524" layer="91"/>
<wire x1="584.2" y1="200.66" x2="594.36" y2="200.66" width="0.1524" layer="91"/>
<junction x="594.36" y="200.66"/>
<pinref part="C42" gate="G$1" pin="2"/>
<wire x1="574.04" y1="203.2" x2="574.04" y2="200.66" width="0.1524" layer="91"/>
<wire x1="574.04" y1="200.66" x2="584.2" y2="200.66" width="0.1524" layer="91"/>
<junction x="584.2" y="200.66"/>
<pinref part="C43" gate="G$1" pin="2"/>
<wire x1="622.3" y1="203.2" x2="622.3" y2="200.66" width="0.1524" layer="91"/>
<wire x1="622.3" y1="200.66" x2="607.06" y2="200.66" width="0.1524" layer="91"/>
<junction x="607.06" y="200.66"/>
<pinref part="C44" gate="G$1" pin="2"/>
<wire x1="635" y1="203.2" x2="635" y2="200.66" width="0.1524" layer="91"/>
<wire x1="635" y1="200.66" x2="622.3" y2="200.66" width="0.1524" layer="91"/>
<junction x="622.3" y="200.66"/>
<pinref part="C46" gate="G$1" pin="2"/>
<wire x1="645.16" y1="203.2" x2="645.16" y2="200.66" width="0.1524" layer="91"/>
<wire x1="645.16" y1="200.66" x2="635" y2="200.66" width="0.1524" layer="91"/>
<junction x="635" y="200.66"/>
</segment>
<segment>
<pinref part="GND53" gate="1" pin="GND"/>
<pinref part="C47" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="C48" gate="G$1" pin="2"/>
<pinref part="GND56" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C49" gate="G$1" pin="-"/>
<pinref part="GND57" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C50" gate="G$1" pin="-"/>
<pinref part="GND58" gate="1" pin="GND"/>
<wire x1="635" y1="96.52" x2="635" y2="93.98" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C63" gate="G$1" pin="-"/>
<wire x1="652.78" y1="114.3" x2="652.78" y2="111.76" width="0.1524" layer="91"/>
<wire x1="652.78" y1="111.76" x2="660.4" y2="111.76" width="0.1524" layer="91"/>
<pinref part="C65" gate="G$1" pin="2"/>
<wire x1="660.4" y1="111.76" x2="660.4" y2="114.3" width="0.1524" layer="91"/>
<pinref part="GND61" gate="1" pin="GND"/>
<junction x="660.4" y="111.76"/>
</segment>
<segment>
<pinref part="C64" gate="G$1" pin="-"/>
<wire x1="650.24" y1="96.52" x2="650.24" y2="93.98" width="0.1524" layer="91"/>
<wire x1="650.24" y1="93.98" x2="660.4" y2="93.98" width="0.1524" layer="91"/>
<pinref part="C66" gate="G$1" pin="2"/>
<wire x1="660.4" y1="93.98" x2="660.4" y2="96.52" width="0.1524" layer="91"/>
<junction x="660.4" y="93.98"/>
<pinref part="GND62" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C62" gate="G$1" pin="2"/>
<wire x1="629.92" y1="139.7" x2="629.92" y2="137.16" width="0.1524" layer="91"/>
<wire x1="629.92" y1="137.16" x2="640.08" y2="137.16" width="0.1524" layer="91"/>
<pinref part="C55" gate="G$1" pin="2"/>
<wire x1="640.08" y1="137.16" x2="650.24" y2="137.16" width="0.1524" layer="91"/>
<wire x1="650.24" y1="137.16" x2="660.4" y2="137.16" width="0.1524" layer="91"/>
<wire x1="660.4" y1="137.16" x2="670.56" y2="137.16" width="0.1524" layer="91"/>
<wire x1="670.56" y1="137.16" x2="680.72" y2="137.16" width="0.1524" layer="91"/>
<wire x1="680.72" y1="137.16" x2="680.72" y2="139.7" width="0.1524" layer="91"/>
<pinref part="C54" gate="G$1" pin="2"/>
<wire x1="670.56" y1="139.7" x2="670.56" y2="137.16" width="0.1524" layer="91"/>
<junction x="670.56" y="137.16"/>
<pinref part="C53" gate="G$1" pin="2"/>
<wire x1="660.4" y1="139.7" x2="660.4" y2="137.16" width="0.1524" layer="91"/>
<junction x="660.4" y="137.16"/>
<pinref part="C52" gate="G$1" pin="2"/>
<wire x1="650.24" y1="139.7" x2="650.24" y2="137.16" width="0.1524" layer="91"/>
<junction x="650.24" y="137.16"/>
<pinref part="C51" gate="G$1" pin="2"/>
<wire x1="640.08" y1="139.7" x2="640.08" y2="137.16" width="0.1524" layer="91"/>
<junction x="640.08" y="137.16"/>
<pinref part="GND60" gate="1" pin="GND"/>
<pinref part="C22" gate="G$1" pin="2"/>
<wire x1="680.72" y1="137.16" x2="690.88" y2="137.16" width="0.1524" layer="91"/>
<wire x1="690.88" y1="137.16" x2="690.88" y2="139.7" width="0.1524" layer="91"/>
<junction x="680.72" y="137.16"/>
</segment>
<segment>
<pinref part="C68" gate="G$1" pin="2"/>
<pinref part="GND64" gate="1" pin="GND"/>
<wire x1="657.86" y1="157.48" x2="665.48" y2="157.48" width="0.1524" layer="91"/>
<pinref part="C69" gate="G$1" pin="2"/>
<wire x1="657.86" y1="170.18" x2="665.48" y2="170.18" width="0.1524" layer="91"/>
<wire x1="665.48" y1="157.48" x2="665.48" y2="170.18" width="0.1524" layer="91"/>
<junction x="665.48" y="157.48"/>
</segment>
<segment>
<pinref part="M1" gate="M$1" pin="P$2"/>
<pinref part="GND15" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="C17" gate="G$1" pin="2"/>
<pinref part="GND30" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="DD2" gate=".3" pin="BOOT0"/>
<wire x1="586.74" y1="119.38" x2="584.2" y2="119.38" width="0.1524" layer="91"/>
<wire x1="584.2" y1="119.38" x2="584.2" y2="114.3" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VSSA"/>
<wire x1="584.2" y1="114.3" x2="584.2" y2="111.76" width="0.1524" layer="91"/>
<wire x1="584.2" y1="111.76" x2="584.2" y2="109.22" width="0.1524" layer="91"/>
<wire x1="584.2" y1="109.22" x2="584.2" y2="106.68" width="0.1524" layer="91"/>
<wire x1="584.2" y1="106.68" x2="584.2" y2="104.14" width="0.1524" layer="91"/>
<wire x1="584.2" y1="104.14" x2="586.74" y2="104.14" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VSS@2"/>
<wire x1="586.74" y1="106.68" x2="584.2" y2="106.68" width="0.1524" layer="91"/>
<junction x="584.2" y="106.68"/>
<pinref part="DD2" gate=".3" pin="VSS@1"/>
<wire x1="586.74" y1="109.22" x2="584.2" y2="109.22" width="0.1524" layer="91"/>
<junction x="584.2" y="109.22"/>
<pinref part="DD2" gate=".3" pin="VSS"/>
<wire x1="586.74" y1="111.76" x2="584.2" y2="111.76" width="0.1524" layer="91"/>
<junction x="584.2" y="111.76"/>
<pinref part="DD2" gate=".3" pin="VSS@3"/>
<wire x1="586.74" y1="114.3" x2="584.2" y2="114.3" width="0.1524" layer="91"/>
<junction x="584.2" y="114.3"/>
<pinref part="GND31" gate="1" pin="GND"/>
<junction x="584.2" y="104.14"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="FILT+"/>
<pinref part="C9" gate="G$1" pin="1"/>
<wire x1="543.56" y1="287.02" x2="551.18" y2="287.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="AFILTA"/>
<pinref part="C10" gate="G$1" pin="1"/>
<wire x1="543.56" y1="289.56" x2="561.34" y2="289.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="AFILTB"/>
<pinref part="C11" gate="G$1" pin="1"/>
<wire x1="543.56" y1="292.1" x2="571.5" y2="292.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="VQ"/>
<pinref part="C12" gate="G$1" pin="1"/>
<wire x1="543.56" y1="294.64" x2="581.66" y2="294.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="HP/LINE_OUTB"/>
<pinref part="C13" gate="G$1" pin="1"/>
<wire x1="543.56" y1="345.44" x2="553.72" y2="345.44" width="0.1524" layer="91"/>
<wire x1="553.72" y1="345.44" x2="553.72" y2="342.9" width="0.1524" layer="91"/>
<pinref part="X1" gate="X$1" pin="B"/>
<wire x1="596.9" y1="340.36" x2="594.36" y2="340.36" width="0.1524" layer="91"/>
<wire x1="594.36" y1="340.36" x2="594.36" y2="345.44" width="0.1524" layer="91"/>
<wire x1="594.36" y1="345.44" x2="581.66" y2="345.44" width="0.1524" layer="91"/>
<junction x="553.72" y="345.44"/>
<pinref part="VD4" gate="G$1" pin="P$2"/>
<wire x1="581.66" y1="345.44" x2="553.72" y2="345.44" width="0.1524" layer="91"/>
<wire x1="586.74" y1="363.22" x2="581.66" y2="363.22" width="0.1524" layer="91"/>
<wire x1="581.66" y1="363.22" x2="581.66" y2="345.44" width="0.1524" layer="91"/>
<junction x="581.66" y="345.44"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="HP/LINE_OUTA"/>
<pinref part="C14" gate="G$1" pin="1"/>
<wire x1="543.56" y1="347.98" x2="556.26" y2="347.98" width="0.1524" layer="91"/>
<wire x1="556.26" y1="347.98" x2="568.96" y2="347.98" width="0.1524" layer="91"/>
<wire x1="568.96" y1="347.98" x2="568.96" y2="342.9" width="0.1524" layer="91"/>
<pinref part="X1" gate="X$1" pin="A"/>
<wire x1="568.96" y1="347.98" x2="596.9" y2="347.98" width="0.1524" layer="91"/>
<wire x1="596.9" y1="347.98" x2="596.9" y2="342.9" width="0.1524" layer="91"/>
<junction x="568.96" y="347.98"/>
<pinref part="VD3" gate="G$1" pin="P$2"/>
<wire x1="558.8" y1="363.22" x2="556.26" y2="363.22" width="0.1524" layer="91"/>
<wire x1="556.26" y1="363.22" x2="556.26" y2="347.98" width="0.1524" layer="91"/>
<junction x="556.26" y="347.98"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="FLYN"/>
<pinref part="C8" gate="G$1" pin="1"/>
<wire x1="502.92" y1="322.58" x2="492.76" y2="322.58" width="0.1524" layer="91"/>
<wire x1="492.76" y1="322.58" x2="492.76" y2="320.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="C8" gate="G$1" pin="2"/>
<pinref part="DD1" gate="DD$1" pin="FLYP"/>
<wire x1="492.76" y1="312.42" x2="492.76" y2="309.88" width="0.1524" layer="91"/>
<wire x1="492.76" y1="309.88" x2="502.92" y2="309.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="-VHPFILT"/>
<pinref part="C7" gate="G$1" pin="1"/>
<wire x1="502.92" y1="325.12" x2="485.14" y2="325.12" width="0.1524" layer="91"/>
<wire x1="485.14" y1="325.12" x2="485.14" y2="320.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SDA" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="SDA"/>
<wire x1="502.92" y1="347.98" x2="490.22" y2="347.98" width="0.1524" layer="91"/>
<label x="482.6" y="347.98" size="1.778" layer="95"/>
<pinref part="R52" gate="G$1" pin="1"/>
<wire x1="490.22" y1="347.98" x2="482.6" y2="347.98" width="0.1524" layer="91"/>
<wire x1="490.22" y1="350.52" x2="490.22" y2="347.98" width="0.1524" layer="91"/>
<junction x="490.22" y="347.98"/>
</segment>
<segment>
<label x="551.18" y="142.24" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB11"/>
<wire x1="551.18" y1="142.24" x2="533.4" y2="142.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SCL" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="SCL"/>
<wire x1="502.92" y1="345.44" x2="500.38" y2="345.44" width="0.1524" layer="91"/>
<label x="482.6" y="345.44" size="1.778" layer="95"/>
<pinref part="R51" gate="G$1" pin="1"/>
<wire x1="500.38" y1="345.44" x2="482.6" y2="345.44" width="0.1524" layer="91"/>
<wire x1="500.38" y1="350.52" x2="500.38" y2="345.44" width="0.1524" layer="91"/>
<junction x="500.38" y="345.44"/>
</segment>
<segment>
<label x="551.18" y="144.78" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB10"/>
<wire x1="551.18" y1="144.78" x2="533.4" y2="144.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="I2S_MCK" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="MCLK"/>
<wire x1="502.92" y1="337.82" x2="487.68" y2="337.82" width="0.1524" layer="91"/>
<label x="487.68" y="337.82" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="508" y1="99.06" x2="492.76" y2="99.06" width="0.1524" layer="91"/>
<label x="492.76" y="99.06" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC6"/>
</segment>
</net>
<net name="I2S_SCK" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="SCLK"/>
<wire x1="502.92" y1="335.28" x2="487.68" y2="335.28" width="0.1524" layer="91"/>
<label x="487.68" y="335.28" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="533.4" y1="137.16" x2="551.18" y2="137.16" width="0.1524" layer="91"/>
<label x="551.18" y="137.16" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB13"/>
</segment>
</net>
<net name="I2S_SD" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="SDIN"/>
<wire x1="502.92" y1="332.74" x2="487.68" y2="332.74" width="0.1524" layer="91"/>
<label x="487.68" y="332.74" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="533.4" y1="132.08" x2="551.18" y2="132.08" width="0.1524" layer="91"/>
<label x="551.18" y="132.08" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB15"/>
</segment>
</net>
<net name="I2S_WS" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="LRCK"/>
<wire x1="502.92" y1="330.2" x2="487.68" y2="330.2" width="0.1524" layer="91"/>
<label x="487.68" y="330.2" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="533.4" y1="139.7" x2="551.18" y2="139.7" width="0.1524" layer="91"/>
<label x="551.18" y="139.7" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB12"/>
</segment>
</net>
<net name="#PRST" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="#RESET"/>
<wire x1="502.92" y1="327.66" x2="474.98" y2="327.66" width="0.1524" layer="91"/>
<label x="464.82" y="327.66" size="1.778" layer="95"/>
<wire x1="474.98" y1="322.58" x2="474.98" y2="327.66" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="474.98" y1="327.66" x2="464.82" y2="327.66" width="0.1524" layer="91"/>
<junction x="474.98" y="327.66"/>
</segment>
<segment>
<wire x1="508" y1="96.52" x2="492.76" y2="96.52" width="0.1524" layer="91"/>
<label x="492.76" y="96.52" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC7"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="C13" gate="G$1" pin="2"/>
<pinref part="R2" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="C14" gate="G$1" pin="2"/>
<pinref part="R3" gate="G$1" pin="2"/>
</segment>
</net>
<net name="BTN_ADC" class="0">
<segment>
<label x="614.68" y="292.1" size="1.778" layer="95" rot="MR0"/>
<wire x1="589.28" y1="292.1" x2="601.98" y2="292.1" width="0.1524" layer="91"/>
<wire x1="601.98" y1="292.1" x2="614.68" y2="292.1" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="2"/>
<wire x1="589.28" y1="314.96" x2="586.74" y2="314.96" width="0.1524" layer="91"/>
<junction x="589.28" y="314.96"/>
<wire x1="589.28" y1="314.96" x2="589.28" y2="292.1" width="0.1524" layer="91"/>
<pinref part="VD5" gate="G$1" pin="P$5"/>
<wire x1="589.28" y1="314.96" x2="591.82" y2="314.96" width="0.1524" layer="91"/>
<pinref part="X1" gate="X$1" pin="BTN"/>
<wire x1="596.9" y1="332.74" x2="596.9" y2="322.58" width="0.1524" layer="91"/>
<wire x1="596.9" y1="322.58" x2="589.28" y2="322.58" width="0.1524" layer="91"/>
<wire x1="589.28" y1="322.58" x2="589.28" y2="314.96" width="0.1524" layer="91"/>
<pinref part="C47" gate="G$1" pin="1"/>
<wire x1="589.28" y1="292.1" x2="589.28" y2="287.02" width="0.1524" layer="91"/>
<junction x="589.28" y="292.1"/>
<pinref part="R6" gate="G$1" pin="2"/>
<wire x1="601.98" y1="289.56" x2="601.98" y2="292.1" width="0.1524" layer="91"/>
<junction x="601.98" y="292.1"/>
</segment>
<segment>
<label x="492.76" y="114.3" size="1.778" layer="95"/>
<wire x1="508" y1="114.3" x2="492.76" y2="114.3" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".2" pin="PC0"/>
</segment>
</net>
<net name="BTN_OUT" class="0">
<segment>
<pinref part="R6" gate="G$1" pin="1"/>
<wire x1="601.98" y1="276.86" x2="601.98" y2="279.4" width="0.1524" layer="91"/>
<wire x1="601.98" y1="276.86" x2="614.68" y2="276.86" width="0.1524" layer="91"/>
<label x="614.68" y="276.86" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="508" y1="111.76" x2="492.76" y2="111.76" width="0.1524" layer="91"/>
<label x="492.76" y="111.76" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC1"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="VP"/>
<wire x1="543.56" y1="325.12" x2="548.64" y2="325.12" width="0.1524" layer="91"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="548.64" y1="325.12" x2="548.64" y2="322.58" width="0.1524" layer="91"/>
<pinref part="DD1" gate="DD$1" pin="VP@1"/>
<wire x1="548.64" y1="322.58" x2="548.64" y2="314.96" width="0.1524" layer="91"/>
<wire x1="548.64" y1="314.96" x2="548.64" y2="309.88" width="0.1524" layer="91"/>
<wire x1="543.56" y1="322.58" x2="548.64" y2="322.58" width="0.1524" layer="91"/>
<junction x="548.64" y="322.58"/>
<wire x1="548.64" y1="314.96" x2="561.34" y2="314.96" width="0.1524" layer="91"/>
<junction x="548.64" y="314.96"/>
<pinref part="C6" gate="G$1" pin="1"/>
<wire x1="561.34" y1="314.96" x2="561.34" y2="309.88" width="0.1524" layer="91"/>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<wire x1="548.64" y1="327.66" x2="548.64" y2="325.12" width="0.1524" layer="91"/>
<junction x="548.64" y="325.12"/>
</segment>
<segment>
<pinref part="DD1" gate="DD$1" pin="VL"/>
<pinref part="C4" gate="G$1" pin="1"/>
<wire x1="502.92" y1="289.56" x2="497.84" y2="289.56" width="0.1524" layer="91"/>
<wire x1="497.84" y1="289.56" x2="490.22" y2="289.56" width="0.1524" layer="91"/>
<wire x1="490.22" y1="289.56" x2="490.22" y2="287.02" width="0.1524" layer="91"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<junction x="497.84" y="289.56"/>
</segment>
<segment>
<pinref part="C16" gate="G$1" pin="1"/>
<pinref part="+3V3" gate="G$1" pin="+3V3"/>
<pinref part="D1" gate="D$1" pin="VDD2"/>
<pinref part="D1" gate="D$1" pin="VDD1"/>
<wire x1="756.92" y1="353.06" x2="756.92" y2="355.6" width="0.1524" layer="91"/>
<wire x1="777.24" y1="353.06" x2="756.92" y2="353.06" width="0.1524" layer="91"/>
<junction x="777.24" y="353.06"/>
<junction x="756.92" y="353.06"/>
</segment>
<segment>
<pinref part="+3V6" gate="G$1" pin="+3V3"/>
<pinref part="R4" gate="G$1" pin="1"/>
<wire x1="576.58" y1="314.96" x2="574.04" y2="314.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R32" gate="G$1" pin="2"/>
<wire x1="706.12" y1="365.76" x2="698.5" y2="365.76" width="0.1524" layer="91"/>
<pinref part="R30" gate="G$1" pin="2"/>
<wire x1="698.5" y1="365.76" x2="690.88" y2="365.76" width="0.1524" layer="91"/>
<wire x1="690.88" y1="365.76" x2="683.26" y2="365.76" width="0.1524" layer="91"/>
<junction x="690.88" y="365.76"/>
<pinref part="R29" gate="G$1" pin="2"/>
<wire x1="683.26" y1="358.14" x2="683.26" y2="365.76" width="0.1524" layer="91"/>
<pinref part="R31" gate="G$1" pin="2"/>
<wire x1="698.5" y1="358.14" x2="698.5" y2="365.76" width="0.1524" layer="91"/>
<junction x="698.5" y="365.76"/>
<pinref part="R33" gate="G$1" pin="2"/>
<wire x1="713.74" y1="358.14" x2="713.74" y2="365.76" width="0.1524" layer="91"/>
<wire x1="713.74" y1="365.76" x2="706.12" y2="365.76" width="0.1524" layer="91"/>
<junction x="706.12" y="365.76"/>
<pinref part="+3V9" gate="G$1" pin="+3V3"/>
<junction x="683.26" y="365.76"/>
</segment>
<segment>
<pinref part="+3V14" gate="G$1" pin="+3V3"/>
<pinref part="C35" gate="G$1" pin="1"/>
<wire x1="673.1" y1="279.4" x2="673.1" y2="294.64" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="VDD_IO"/>
<pinref part="DD5" gate="G$1" pin="RESERVED"/>
<wire x1="673.1" y1="294.64" x2="673.1" y2="297.18" width="0.1524" layer="91"/>
<wire x1="678.18" y1="297.18" x2="680.72" y2="297.18" width="0.1524" layer="91"/>
<wire x1="680.72" y1="292.1" x2="678.18" y2="292.1" width="0.1524" layer="91"/>
<wire x1="678.18" y1="292.1" x2="678.18" y2="294.64" width="0.1524" layer="91"/>
<junction x="678.18" y="297.18"/>
<pinref part="DD5" gate="G$1" pin="VDD"/>
<wire x1="678.18" y1="294.64" x2="678.18" y2="297.18" width="0.1524" layer="91"/>
<wire x1="680.72" y1="294.64" x2="678.18" y2="294.64" width="0.1524" layer="91"/>
<junction x="678.18" y="294.64"/>
<wire x1="678.18" y1="297.18" x2="678.18" y2="304.8" width="0.1524" layer="91"/>
<wire x1="678.18" y1="304.8" x2="721.36" y2="304.8" width="0.1524" layer="91"/>
<wire x1="721.36" y1="304.8" x2="721.36" y2="297.18" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="CS.I2C_SPI"/>
<wire x1="721.36" y1="297.18" x2="718.82" y2="297.18" width="0.1524" layer="91"/>
<wire x1="678.18" y1="294.64" x2="673.1" y2="294.64" width="0.1524" layer="91"/>
<junction x="673.1" y="294.64"/>
</segment>
<segment>
<pinref part="R51" gate="G$1" pin="2"/>
<pinref part="R52" gate="G$1" pin="2"/>
<wire x1="500.38" y1="360.68" x2="495.3" y2="360.68" width="0.1524" layer="91"/>
<pinref part="+3V16" gate="G$1" pin="+3V3"/>
<wire x1="495.3" y1="360.68" x2="490.22" y2="360.68" width="0.1524" layer="91"/>
<junction x="495.3" y="360.68"/>
</segment>
<segment>
<pinref part="DA2" gate="G$1" pin="VOUT"/>
<wire x1="619.76" y1="215.9" x2="635" y2="215.9" width="0.1524" layer="91"/>
<pinref part="C44" gate="G$1" pin="1"/>
<wire x1="635" y1="215.9" x2="635" y2="210.82" width="0.1524" layer="91"/>
<wire x1="635" y1="215.9" x2="645.16" y2="215.9" width="0.1524" layer="91"/>
<junction x="635" y="215.9"/>
<pinref part="C46" gate="G$1" pin="1"/>
<wire x1="645.16" y1="215.9" x2="645.16" y2="210.82" width="0.1524" layer="91"/>
<pinref part="+3V17" gate="G$1" pin="+3V3"/>
<junction x="645.16" y="215.9"/>
</segment>
<segment>
<pinref part="C18" gate="G$1" pin="1"/>
<wire x1="668.02" y1="365.76" x2="668.02" y2="363.22" width="0.1524" layer="91"/>
<wire x1="678.18" y1="365.76" x2="668.02" y2="365.76" width="0.1524" layer="91"/>
<pinref part="X2" gate="X$1" pin="VDD"/>
<wire x1="678.18" y1="347.98" x2="678.18" y2="365.76" width="0.1524" layer="91"/>
<pinref part="+3V7" gate="G$1" pin="+3V3"/>
<junction x="668.02" y="365.76"/>
</segment>
<segment>
<pinref part="R55" gate="G$1" pin="2"/>
<pinref part="+3V18" gate="G$1" pin="+3V3"/>
</segment>
<segment>
<pinref part="C51" gate="G$1" pin="1"/>
<wire x1="640.08" y1="147.32" x2="640.08" y2="149.86" width="0.1524" layer="91"/>
<wire x1="640.08" y1="149.86" x2="650.24" y2="149.86" width="0.1524" layer="91"/>
<pinref part="C55" gate="G$1" pin="1"/>
<wire x1="650.24" y1="149.86" x2="660.4" y2="149.86" width="0.1524" layer="91"/>
<wire x1="660.4" y1="149.86" x2="670.56" y2="149.86" width="0.1524" layer="91"/>
<wire x1="670.56" y1="149.86" x2="680.72" y2="149.86" width="0.1524" layer="91"/>
<wire x1="680.72" y1="149.86" x2="680.72" y2="147.32" width="0.1524" layer="91"/>
<pinref part="C54" gate="G$1" pin="1"/>
<wire x1="670.56" y1="147.32" x2="670.56" y2="149.86" width="0.1524" layer="91"/>
<junction x="670.56" y="149.86"/>
<pinref part="C53" gate="G$1" pin="1"/>
<wire x1="660.4" y1="147.32" x2="660.4" y2="149.86" width="0.1524" layer="91"/>
<junction x="660.4" y="149.86"/>
<pinref part="C52" gate="G$1" pin="1"/>
<wire x1="650.24" y1="147.32" x2="650.24" y2="149.86" width="0.1524" layer="91"/>
<junction x="650.24" y="149.86"/>
<wire x1="640.08" y1="149.86" x2="629.92" y2="149.86" width="0.1524" layer="91"/>
<junction x="640.08" y="149.86"/>
<pinref part="C62" gate="G$1" pin="1"/>
<wire x1="629.92" y1="147.32" x2="629.92" y2="149.86" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VBAT"/>
<wire x1="622.3" y1="152.4" x2="629.92" y2="152.4" width="0.1524" layer="91"/>
<wire x1="629.92" y1="152.4" x2="629.92" y2="149.86" width="0.1524" layer="91"/>
<junction x="629.92" y="149.86"/>
<wire x1="629.92" y1="149.86" x2="624.84" y2="149.86" width="0.1524" layer="91"/>
<wire x1="624.84" y1="149.86" x2="624.84" y2="147.32" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VDD@5"/>
<wire x1="624.84" y1="147.32" x2="624.84" y2="144.78" width="0.1524" layer="91"/>
<wire x1="624.84" y1="144.78" x2="624.84" y2="142.24" width="0.1524" layer="91"/>
<wire x1="624.84" y1="142.24" x2="624.84" y2="139.7" width="0.1524" layer="91"/>
<wire x1="624.84" y1="139.7" x2="624.84" y2="137.16" width="0.1524" layer="91"/>
<wire x1="624.84" y1="137.16" x2="622.3" y2="137.16" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VDD@4"/>
<wire x1="622.3" y1="139.7" x2="624.84" y2="139.7" width="0.1524" layer="91"/>
<junction x="624.84" y="139.7"/>
<pinref part="DD2" gate=".3" pin="VDD@3"/>
<wire x1="622.3" y1="142.24" x2="624.84" y2="142.24" width="0.1524" layer="91"/>
<junction x="624.84" y="142.24"/>
<pinref part="DD2" gate=".3" pin="VDD@2"/>
<wire x1="624.84" y1="144.78" x2="622.3" y2="144.78" width="0.1524" layer="91"/>
<junction x="624.84" y="144.78"/>
<pinref part="DD2" gate=".3" pin="VDD@1"/>
<wire x1="624.84" y1="147.32" x2="622.3" y2="147.32" width="0.1524" layer="91"/>
<junction x="624.84" y="147.32"/>
<pinref part="DD2" gate=".3" pin="VDD"/>
<wire x1="624.84" y1="149.86" x2="622.3" y2="149.86" width="0.1524" layer="91"/>
<junction x="624.84" y="149.86"/>
<pinref part="C22" gate="G$1" pin="1"/>
<wire x1="680.72" y1="149.86" x2="690.88" y2="149.86" width="0.1524" layer="91"/>
<wire x1="690.88" y1="149.86" x2="690.88" y2="147.32" width="0.1524" layer="91"/>
<junction x="680.72" y="149.86"/>
<pinref part="+3V4" gate="G$1" pin="+3V3"/>
<junction x="690.88" y="149.86"/>
</segment>
<segment>
<pinref part="VD3" gate="G$1" pin="P$1"/>
<wire x1="558.8" y1="368.3" x2="556.26" y2="368.3" width="0.1524" layer="91"/>
<wire x1="556.26" y1="368.3" x2="556.26" y2="378.46" width="0.1524" layer="91"/>
<wire x1="556.26" y1="378.46" x2="581.66" y2="378.46" width="0.1524" layer="91"/>
<pinref part="+3V10" gate="G$1" pin="+3V3"/>
<wire x1="581.66" y1="378.46" x2="581.66" y2="368.3" width="0.1524" layer="91"/>
<junction x="581.66" y="378.46"/>
<pinref part="VD3" gate="G$1" pin="P$5"/>
<wire x1="581.66" y1="368.3" x2="579.12" y2="368.3" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="VD4" gate="G$1" pin="P$3"/>
<wire x1="586.74" y1="358.14" x2="584.2" y2="358.14" width="0.1524" layer="91"/>
<wire x1="584.2" y1="358.14" x2="584.2" y2="378.46" width="0.1524" layer="91"/>
<wire x1="584.2" y1="378.46" x2="609.6" y2="378.46" width="0.1524" layer="91"/>
<wire x1="609.6" y1="378.46" x2="609.6" y2="358.14" width="0.1524" layer="91"/>
<pinref part="VD4" gate="G$1" pin="P$4"/>
<wire x1="609.6" y1="358.14" x2="607.06" y2="358.14" width="0.1524" layer="91"/>
<pinref part="+3V11" gate="G$1" pin="+3V3"/>
<junction x="609.6" y="378.46"/>
</segment>
</net>
<net name="+2V5" class="0">
<segment>
<pinref part="DD1" gate="DD$1" pin="VD"/>
<wire x1="502.92" y1="299.72" x2="500.38" y2="299.72" width="0.1524" layer="91"/>
<wire x1="500.38" y1="299.72" x2="500.38" y2="302.26" width="0.1524" layer="91"/>
<pinref part="DD1" gate="DD$1" pin="+VHP"/>
<wire x1="500.38" y1="302.26" x2="500.38" y2="304.8" width="0.1524" layer="91"/>
<wire x1="500.38" y1="304.8" x2="502.92" y2="304.8" width="0.1524" layer="91"/>
<pinref part="DD1" gate="DD$1" pin="VA"/>
<wire x1="502.92" y1="302.26" x2="500.38" y2="302.26" width="0.1524" layer="91"/>
<junction x="500.38" y="302.26"/>
<pinref part="C1" gate="G$1" pin="1"/>
<wire x1="500.38" y1="304.8" x2="487.68" y2="304.8" width="0.1524" layer="91"/>
<wire x1="487.68" y1="304.8" x2="474.98" y2="304.8" width="0.1524" layer="91"/>
<wire x1="474.98" y1="304.8" x2="464.82" y2="304.8" width="0.1524" layer="91"/>
<wire x1="464.82" y1="304.8" x2="454.66" y2="304.8" width="0.1524" layer="91"/>
<wire x1="454.66" y1="304.8" x2="454.66" y2="302.26" width="0.1524" layer="91"/>
<junction x="500.38" y="304.8"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="464.82" y1="302.26" x2="464.82" y2="304.8" width="0.1524" layer="91"/>
<junction x="464.82" y="304.8"/>
<pinref part="C3" gate="G$1" pin="1"/>
<wire x1="474.98" y1="302.26" x2="474.98" y2="304.8" width="0.1524" layer="91"/>
<junction x="474.98" y="304.8"/>
<pinref part="+2V1" gate="G$1" pin="+2V5"/>
<junction x="454.66" y="304.8"/>
<pinref part="C15" gate="G$1" pin="+"/>
<wire x1="487.68" y1="304.8" x2="487.68" y2="302.26" width="0.1524" layer="91"/>
<junction x="487.68" y="304.8"/>
</segment>
<segment>
<pinref part="DA1" gate="G$1" pin="VOUT"/>
<wire x1="619.76" y1="248.92" x2="635" y2="248.92" width="0.1524" layer="91"/>
<pinref part="C39" gate="G$1" pin="1"/>
<wire x1="635" y1="248.92" x2="635" y2="243.84" width="0.1524" layer="91"/>
<wire x1="635" y1="248.92" x2="645.16" y2="248.92" width="0.1524" layer="91"/>
<junction x="635" y="248.92"/>
<pinref part="C41" gate="G$1" pin="1"/>
<wire x1="645.16" y1="248.92" x2="645.16" y2="243.84" width="0.1524" layer="91"/>
<pinref part="+2V2" gate="G$1" pin="+2V5"/>
<junction x="645.16" y="248.92"/>
</segment>
<segment>
<pinref part="+2V3" gate="G$1" pin="+2V5"/>
<pinref part="L1" gate="G$1" pin="P$1"/>
</segment>
</net>
<net name="B_PPP" class="0">
<segment>
<pinref part="SB1" gate="G$1" pin="INNER"/>
<wire x1="759.46" y1="307.34" x2="751.84" y2="307.34" width="0.1524" layer="91"/>
<label x="759.46" y="307.34" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="558.8" y1="238.76" x2="548.64" y2="238.76" width="0.1524" layer="91"/>
<label x="558.8" y="238.76" size="1.778" layer="95" rot="MR0"/>
<pinref part="VD2" gate="G$1" pin="C"/>
<label x="558.8" y="238.76" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<label x="492.76" y="170.18" size="1.778" layer="95"/>
<wire x1="492.76" y1="170.18" x2="508" y2="170.18" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".1" pin="PA0"/>
</segment>
</net>
<net name="B_ESC" class="0">
<segment>
<pinref part="SB2" gate="G$1" pin="INNER"/>
<wire x1="759.46" y1="299.72" x2="751.84" y2="299.72" width="0.1524" layer="91"/>
<label x="759.46" y="299.72" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<pinref part="DD2" gate=".2" pin="PC15"/>
<wire x1="508" y1="76.2" x2="492.76" y2="76.2" width="0.1524" layer="91"/>
<label x="492.76" y="76.2" size="1.778" layer="95"/>
</segment>
</net>
<net name="B_1" class="0">
<segment>
<pinref part="SB6" gate="G$1" pin="INNER"/>
<wire x1="759.46" y1="292.1" x2="751.84" y2="292.1" width="0.1524" layer="91"/>
<label x="759.46" y="292.1" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<pinref part="DD2" gate=".2" pin="PD11"/>
<wire x1="533.4" y1="86.36" x2="548.64" y2="86.36" width="0.1524" layer="91"/>
<label x="548.64" y="86.36" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="B_4" class="0">
<segment>
<pinref part="SB9" gate="G$1" pin="INNER"/>
<wire x1="759.46" y1="284.48" x2="751.84" y2="284.48" width="0.1524" layer="91"/>
<label x="759.46" y="284.48" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="492.76" y1="132.08" x2="508" y2="132.08" width="0.1524" layer="91"/>
<label x="492.76" y="132.08" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA15"/>
</segment>
</net>
<net name="B_7" class="0">
<segment>
<pinref part="SB12" gate="G$1" pin="INNER"/>
<wire x1="759.46" y1="276.86" x2="751.84" y2="276.86" width="0.1524" layer="91"/>
<label x="759.46" y="276.86" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="574.04" y1="139.7" x2="586.74" y2="139.7" width="0.1524" layer="91"/>
<label x="574.04" y="139.7" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE12"/>
</segment>
</net>
<net name="B_AST" class="0">
<segment>
<pinref part="SB15" gate="G$1" pin="INNER"/>
<wire x1="759.46" y1="269.24" x2="751.84" y2="269.24" width="0.1524" layer="91"/>
<label x="759.46" y="269.24" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="574.04" y1="137.16" x2="586.74" y2="137.16" width="0.1524" layer="91"/>
<label x="574.04" y="137.16" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE13"/>
</segment>
</net>
<net name="B_2" class="0">
<segment>
<wire x1="779.78" y1="292.1" x2="772.16" y2="292.1" width="0.1524" layer="91"/>
<label x="779.78" y="292.1" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB7" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="548.64" y1="88.9" x2="533.4" y2="88.9" width="0.1524" layer="91"/>
<label x="548.64" y="88.9" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".2" pin="PD10"/>
</segment>
</net>
<net name="B_5" class="0">
<segment>
<wire x1="779.78" y1="284.48" x2="772.16" y2="284.48" width="0.1524" layer="91"/>
<label x="779.78" y="284.48" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB10" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="132.08" x2="586.74" y2="132.08" width="0.1524" layer="91"/>
<label x="574.04" y="132.08" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE15"/>
</segment>
</net>
<net name="B_8" class="0">
<segment>
<wire x1="779.78" y1="276.86" x2="772.16" y2="276.86" width="0.1524" layer="91"/>
<label x="779.78" y="276.86" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB13" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="548.64" y1="76.2" x2="533.4" y2="76.2" width="0.1524" layer="91"/>
<label x="548.64" y="76.2" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".2" pin="PD15"/>
</segment>
</net>
<net name="B_9" class="0">
<segment>
<wire x1="800.1" y1="276.86" x2="792.48" y2="276.86" width="0.1524" layer="91"/>
<label x="800.1" y="276.86" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB14" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="147.32" x2="586.74" y2="147.32" width="0.1524" layer="91"/>
<label x="574.04" y="147.32" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE9"/>
</segment>
</net>
<net name="B_3" class="0">
<segment>
<wire x1="800.1" y1="292.1" x2="792.48" y2="292.1" width="0.1524" layer="91"/>
<label x="800.1" y="292.1" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB8" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="144.78" x2="586.74" y2="144.78" width="0.1524" layer="91"/>
<label x="574.04" y="144.78" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE10"/>
</segment>
</net>
<net name="B_6" class="0">
<segment>
<wire x1="800.1" y1="284.48" x2="792.48" y2="284.48" width="0.1524" layer="91"/>
<label x="800.1" y="284.48" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB11" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="142.24" x2="586.74" y2="142.24" width="0.1524" layer="91"/>
<label x="574.04" y="142.24" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE11"/>
</segment>
</net>
<net name="B_0" class="0">
<segment>
<wire x1="779.78" y1="269.24" x2="772.16" y2="269.24" width="0.1524" layer="91"/>
<label x="779.78" y="269.24" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB16" gate="G$1" pin="INNER"/>
</segment>
<segment>
<pinref part="DD2" gate=".1" pin="PA8"/>
<wire x1="508" y1="149.86" x2="492.76" y2="149.86" width="0.1524" layer="91"/>
<label x="492.76" y="149.86" size="1.778" layer="95"/>
</segment>
</net>
<net name="B_PND" class="0">
<segment>
<wire x1="800.1" y1="269.24" x2="792.48" y2="269.24" width="0.1524" layer="91"/>
<label x="800.1" y="269.24" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB17" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="152.4" x2="586.74" y2="152.4" width="0.1524" layer="91"/>
<label x="574.04" y="152.4" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE7"/>
</segment>
</net>
<net name="B_UP" class="0">
<segment>
<wire x1="800.1" y1="307.34" x2="792.48" y2="307.34" width="0.1524" layer="91"/>
<label x="800.1" y="307.34" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB3" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="149.86" x2="586.74" y2="149.86" width="0.1524" layer="91"/>
<label x="574.04" y="149.86" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE8"/>
</segment>
</net>
<net name="B_DWN" class="0">
<segment>
<wire x1="800.1" y1="299.72" x2="792.48" y2="299.72" width="0.1524" layer="91"/>
<label x="800.1" y="299.72" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB5" gate="G$1" pin="INNER"/>
</segment>
<segment>
<wire x1="574.04" y1="134.62" x2="586.74" y2="134.62" width="0.1524" layer="91"/>
<label x="574.04" y="134.62" size="1.778" layer="95"/>
<pinref part="DD2" gate=".3" pin="PE14"/>
</segment>
</net>
<net name="B_SEL" class="0">
<segment>
<wire x1="779.78" y1="302.26" x2="772.16" y2="302.26" width="0.1524" layer="91"/>
<label x="779.78" y="302.26" size="1.778" layer="95" rot="MR0"/>
<pinref part="SB4" gate="G$1" pin="INNER"/>
</segment>
<segment>
<label x="548.64" y="81.28" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".2" pin="PD13"/>
<wire x1="548.64" y1="81.28" x2="533.4" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="D1" gate="D$1" pin="BKL"/>
<wire x1="756.92" y1="350.52" x2="764.54" y2="350.52" width="0.1524" layer="91"/>
<wire x1="764.54" y1="350.52" x2="764.54" y2="330.2" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="1"/>
<wire x1="764.54" y1="330.2" x2="772.16" y2="330.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="D_NRST" class="0">
<segment>
<pinref part="D1" gate="D$1" pin="#RES"/>
<wire x1="769.62" y1="358.14" x2="756.92" y2="358.14" width="0.1524" layer="91"/>
<label x="769.62" y="358.14" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="492.76" y1="165.1" x2="508" y2="165.1" width="0.1524" layer="91"/>
<label x="492.76" y="165.1" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA2"/>
</segment>
</net>
<net name="D_SCLK" class="0">
<segment>
<pinref part="D1" gate="D$1" pin="SCLK"/>
<wire x1="769.62" y1="360.68" x2="756.92" y2="360.68" width="0.1524" layer="91"/>
<label x="769.62" y="360.68" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="492.76" y1="157.48" x2="508" y2="157.48" width="0.1524" layer="91"/>
<label x="492.76" y="157.48" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA5"/>
</segment>
</net>
<net name="D_SDIN" class="0">
<segment>
<pinref part="D1" gate="D$1" pin="SDIN"/>
<wire x1="769.62" y1="363.22" x2="756.92" y2="363.22" width="0.1524" layer="91"/>
<label x="769.62" y="363.22" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="492.76" y1="152.4" x2="508" y2="152.4" width="0.1524" layer="91"/>
<label x="492.76" y="152.4" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA7"/>
</segment>
</net>
<net name="D_NCS" class="0">
<segment>
<pinref part="D1" gate="D$1" pin="#CS"/>
<wire x1="769.62" y1="365.76" x2="756.92" y2="365.76" width="0.1524" layer="91"/>
<label x="769.62" y="365.76" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="492.76" y1="160.02" x2="508" y2="160.02" width="0.1524" layer="91"/>
<label x="492.76" y="160.02" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA4"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="R7" gate="G$1" pin="2"/>
<pinref part="VT1" gate="VT$1" pin="D"/>
<wire x1="782.32" y1="330.2" x2="789.94" y2="330.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VBAT" class="1">
<segment>
<pinref part="VT1" gate="VT$1" pin="S"/>
<pinref part="VBAT1" gate="G$1" pin="VBAT"/>
<wire x1="789.94" y1="345.44" x2="789.94" y2="342.9" width="0.1524" layer="91"/>
<pinref part="R9" gate="G$1" pin="1"/>
<wire x1="789.94" y1="342.9" x2="789.94" y2="340.36" width="0.1524" layer="91"/>
<wire x1="792.48" y1="342.9" x2="789.94" y2="342.9" width="0.1524" layer="91"/>
<junction x="789.94" y="342.9"/>
</segment>
<segment>
<pinref part="VBAT5" gate="G$1" pin="VBAT"/>
<pinref part="VT4" gate="VT$1" pin="D"/>
<wire x1="553.72" y1="248.92" x2="548.64" y2="248.92" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C42" gate="G$1" pin="1"/>
<pinref part="DA2" gate="G$1" pin="VIN"/>
<wire x1="574.04" y1="210.82" x2="574.04" y2="215.9" width="0.1524" layer="91"/>
<wire x1="574.04" y1="215.9" x2="584.2" y2="215.9" width="0.1524" layer="91"/>
<pinref part="DA2" gate="G$1" pin="INH"/>
<wire x1="584.2" y1="215.9" x2="594.36" y2="215.9" width="0.1524" layer="91"/>
<wire x1="594.36" y1="213.36" x2="584.2" y2="213.36" width="0.1524" layer="91"/>
<wire x1="584.2" y1="213.36" x2="584.2" y2="215.9" width="0.1524" layer="91"/>
<junction x="584.2" y="215.9"/>
<pinref part="C45" gate="G$1" pin="1"/>
<wire x1="584.2" y1="210.82" x2="584.2" y2="213.36" width="0.1524" layer="91"/>
<junction x="584.2" y="213.36"/>
<pinref part="VBAT4" gate="G$1" pin="VBAT"/>
<junction x="574.04" y="215.9"/>
</segment>
<segment>
<pinref part="C37" gate="G$1" pin="1"/>
<pinref part="DA1" gate="G$1" pin="VIN"/>
<wire x1="574.04" y1="243.84" x2="574.04" y2="248.92" width="0.1524" layer="91"/>
<wire x1="574.04" y1="248.92" x2="584.2" y2="248.92" width="0.1524" layer="91"/>
<pinref part="DA1" gate="G$1" pin="INH"/>
<wire x1="584.2" y1="248.92" x2="594.36" y2="248.92" width="0.1524" layer="91"/>
<wire x1="594.36" y1="246.38" x2="584.2" y2="246.38" width="0.1524" layer="91"/>
<wire x1="584.2" y1="246.38" x2="584.2" y2="248.92" width="0.1524" layer="91"/>
<junction x="584.2" y="248.92"/>
<pinref part="C40" gate="G$1" pin="1"/>
<wire x1="584.2" y1="243.84" x2="584.2" y2="246.38" width="0.1524" layer="91"/>
<junction x="584.2" y="246.38"/>
<pinref part="VBAT3" gate="G$1" pin="VBAT"/>
<junction x="574.04" y="248.92"/>
</segment>
<segment>
<pinref part="VT2" gate="VT$1" pin="S"/>
<pinref part="VBAT2" gate="G$1" pin="VBAT"/>
<wire x1="759.46" y1="185.42" x2="759.46" y2="182.88" width="0.1524" layer="91"/>
<pinref part="C17" gate="G$1" pin="1"/>
<wire x1="746.76" y1="182.88" x2="746.76" y2="185.42" width="0.1524" layer="91"/>
<wire x1="746.76" y1="185.42" x2="759.46" y2="185.42" width="0.1524" layer="91"/>
<junction x="759.46" y="185.42"/>
<pinref part="R8" gate="G$1" pin="1"/>
<wire x1="762" y1="185.42" x2="759.46" y2="185.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="D_NBKL" class="0">
<segment>
<pinref part="VT1" gate="VT$1" pin="G"/>
<wire x1="795.02" y1="337.82" x2="802.64" y2="337.82" width="0.1524" layer="91"/>
<wire x1="802.64" y1="337.82" x2="802.64" y2="342.9" width="0.1524" layer="91"/>
<wire x1="802.64" y1="342.9" x2="802.64" y2="355.6" width="0.1524" layer="91"/>
<wire x1="802.64" y1="355.6" x2="789.94" y2="355.6" width="0.1524" layer="91"/>
<label x="789.94" y="355.6" size="1.778" layer="95"/>
<pinref part="R9" gate="G$1" pin="2"/>
<junction x="802.64" y="342.9"/>
</segment>
<segment>
<wire x1="492.76" y1="162.56" x2="508" y2="162.56" width="0.1524" layer="91"/>
<label x="492.76" y="162.56" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA3"/>
</segment>
</net>
<net name="SD_INS" class="0">
<segment>
<label x="695.96" y="317.5" size="1.778" layer="95" rot="MR0"/>
<wire x1="683.26" y1="317.5" x2="695.96" y2="317.5" width="0.1524" layer="91"/>
<pinref part="X2" gate="X$1" pin="SNS1"/>
<wire x1="678.18" y1="325.12" x2="683.26" y2="325.12" width="0.1524" layer="91"/>
<wire x1="683.26" y1="325.12" x2="683.26" y2="322.58" width="0.1524" layer="91"/>
<wire x1="683.26" y1="322.58" x2="683.26" y2="317.5" width="0.1524" layer="91"/>
<pinref part="X2" gate="X$1" pin="SNS2"/>
<wire x1="678.18" y1="322.58" x2="683.26" y2="322.58" width="0.1524" layer="91"/>
<junction x="683.26" y="322.58"/>
</segment>
<segment>
<label x="548.64" y="111.76" size="1.778" layer="95" rot="MR0"/>
<wire x1="533.4" y1="111.76" x2="548.64" y2="111.76" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".2" pin="PD1"/>
</segment>
</net>
<net name="SD_D1" class="0">
<segment>
<pinref part="X2" gate="X$1" pin="D1"/>
<wire x1="678.18" y1="332.74" x2="713.74" y2="332.74" width="0.1524" layer="91"/>
<label x="726.44" y="332.74" size="1.778" layer="95" rot="MR0"/>
<pinref part="R33" gate="G$1" pin="1"/>
<wire x1="713.74" y1="332.74" x2="726.44" y2="332.74" width="0.1524" layer="91"/>
<wire x1="713.74" y1="332.74" x2="713.74" y2="347.98" width="0.1524" layer="91"/>
<junction x="713.74" y="332.74"/>
</segment>
<segment>
<label x="492.76" y="91.44" size="1.778" layer="95"/>
<wire x1="508" y1="91.44" x2="492.76" y2="91.44" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".2" pin="PC9"/>
</segment>
</net>
<net name="SD_D0" class="0">
<segment>
<pinref part="X2" gate="X$1" pin="D0"/>
<wire x1="726.44" y1="335.28" x2="706.12" y2="335.28" width="0.1524" layer="91"/>
<label x="726.44" y="335.28" size="1.778" layer="95" rot="MR0"/>
<pinref part="R32" gate="G$1" pin="1"/>
<wire x1="706.12" y1="335.28" x2="678.18" y2="335.28" width="0.1524" layer="91"/>
<wire x1="706.12" y1="335.28" x2="706.12" y2="355.6" width="0.1524" layer="91"/>
<junction x="706.12" y="335.28"/>
</segment>
<segment>
<wire x1="492.76" y1="93.98" x2="508" y2="93.98" width="0.1524" layer="91"/>
<label x="492.76" y="93.98" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC8"/>
</segment>
</net>
<net name="SD_CK" class="0">
<segment>
<pinref part="X2" gate="X$1" pin="CK"/>
<wire x1="726.44" y1="337.82" x2="695.96" y2="337.82" width="0.1524" layer="91"/>
<label x="726.44" y="337.82" size="1.778" layer="95" rot="MR0"/>
<wire x1="695.96" y1="337.82" x2="678.18" y2="337.82" width="0.1524" layer="91"/>
<wire x1="695.96" y1="337.82" x2="695.96" y2="327.66" width="0.1524" layer="91"/>
<junction x="695.96" y="337.82"/>
<pinref part="R34" gate="G$1" pin="2"/>
<wire x1="695.96" y1="327.66" x2="693.42" y2="327.66" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="492.76" y1="83.82" x2="508" y2="83.82" width="0.1524" layer="91"/>
<label x="492.76" y="83.82" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC12"/>
</segment>
</net>
<net name="SD_CMD" class="0">
<segment>
<pinref part="X2" gate="X$1" pin="CMD"/>
<wire x1="726.44" y1="340.36" x2="698.5" y2="340.36" width="0.1524" layer="91"/>
<label x="726.44" y="340.36" size="1.778" layer="95" rot="MR0"/>
<pinref part="R31" gate="G$1" pin="1"/>
<wire x1="698.5" y1="340.36" x2="678.18" y2="340.36" width="0.1524" layer="91"/>
<wire x1="698.5" y1="347.98" x2="698.5" y2="340.36" width="0.1524" layer="91"/>
<junction x="698.5" y="340.36"/>
</segment>
<segment>
<wire x1="548.64" y1="109.22" x2="533.4" y2="109.22" width="0.1524" layer="91"/>
<label x="548.64" y="109.22" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".2" pin="PD2"/>
</segment>
</net>
<net name="SD_D3" class="0">
<segment>
<pinref part="X2" gate="X$1" pin="D3"/>
<wire x1="726.44" y1="342.9" x2="690.88" y2="342.9" width="0.1524" layer="91"/>
<label x="726.44" y="342.9" size="1.778" layer="95" rot="MR0"/>
<pinref part="R30" gate="G$1" pin="1"/>
<wire x1="690.88" y1="342.9" x2="678.18" y2="342.9" width="0.1524" layer="91"/>
<wire x1="690.88" y1="355.6" x2="690.88" y2="342.9" width="0.1524" layer="91"/>
<junction x="690.88" y="342.9"/>
</segment>
<segment>
<wire x1="492.76" y1="86.36" x2="508" y2="86.36" width="0.1524" layer="91"/>
<label x="492.76" y="86.36" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC11"/>
</segment>
</net>
<net name="SD_D2" class="0">
<segment>
<pinref part="X2" gate="X$1" pin="D2"/>
<wire x1="726.44" y1="345.44" x2="683.26" y2="345.44" width="0.1524" layer="91"/>
<label x="726.44" y="345.44" size="1.778" layer="95" rot="MR0"/>
<pinref part="R29" gate="G$1" pin="1"/>
<wire x1="683.26" y1="345.44" x2="678.18" y2="345.44" width="0.1524" layer="91"/>
<wire x1="683.26" y1="347.98" x2="683.26" y2="345.44" width="0.1524" layer="91"/>
<junction x="683.26" y="345.44"/>
</segment>
<segment>
<wire x1="492.76" y1="88.9" x2="508" y2="88.9" width="0.1524" layer="91"/>
<label x="492.76" y="88.9" size="1.778" layer="95"/>
<pinref part="DD2" gate=".2" pin="PC10"/>
</segment>
</net>
<net name="ADC_CHG" class="0">
<segment>
<wire x1="441.96" y1="215.9" x2="490.22" y2="215.9" width="0.1524" layer="91"/>
<label x="441.96" y="215.9" size="1.778" layer="95"/>
<pinref part="R35" gate="G$1" pin="2"/>
<wire x1="490.22" y1="213.36" x2="490.22" y2="215.9" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="PROG"/>
<wire x1="502.92" y1="233.68" x2="505.46" y2="233.68" width="0.1524" layer="91"/>
<wire x1="505.46" y1="233.68" x2="505.46" y2="223.52" width="0.1524" layer="91"/>
<wire x1="505.46" y1="223.52" x2="490.22" y2="223.52" width="0.1524" layer="91"/>
<wire x1="490.22" y1="223.52" x2="490.22" y2="215.9" width="0.1524" layer="91"/>
<junction x="490.22" y="215.9"/>
</segment>
<segment>
<pinref part="DD2" gate=".1" pin="PB1"/>
<wire x1="551.18" y1="167.64" x2="533.4" y2="167.64" width="0.1524" layer="91"/>
<label x="551.18" y="167.64" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="ADC_BAT" class="0">
<segment>
<pinref part="R39" gate="G$1" pin="2"/>
<wire x1="523.24" y1="215.9" x2="530.86" y2="215.9" width="0.1524" layer="91"/>
<pinref part="R38" gate="G$1" pin="2"/>
<wire x1="530.86" y1="215.9" x2="530.86" y2="213.36" width="0.1524" layer="91"/>
<junction x="530.86" y="215.9"/>
<wire x1="530.86" y1="215.9" x2="556.26" y2="215.9" width="0.1524" layer="91"/>
<label x="556.26" y="215.9" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<pinref part="DD2" gate=".1" pin="PB0"/>
<wire x1="551.18" y1="170.18" x2="533.4" y2="170.18" width="0.1524" layer="91"/>
<label x="551.18" y="170.18" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="DD3" gate="G$1" pin="VCC"/>
<wire x1="480.06" y1="238.76" x2="467.36" y2="238.76" width="0.1524" layer="91"/>
<pinref part="C21" gate="G$1" pin="1"/>
<wire x1="467.36" y1="238.76" x2="467.36" y2="236.22" width="0.1524" layer="91"/>
<pinref part="R40" gate="G$1" pin="2"/>
<junction x="467.36" y="238.76"/>
</segment>
</net>
<net name="VBAT0" class="1">
<segment>
<pinref part="B1" gate="B$1" pin="+"/>
<wire x1="508" y1="215.9" x2="505.46" y2="215.9" width="0.1524" layer="91"/>
<pinref part="VT3" gate="VT$1" pin="D"/>
<pinref part="DD3" gate="G$1" pin="BAT"/>
<wire x1="502.92" y1="238.76" x2="508" y2="238.76" width="0.1524" layer="91"/>
<wire x1="508" y1="238.76" x2="508" y2="215.9" width="0.1524" layer="91"/>
<junction x="508" y="238.76"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="VT3" gate="VT$1" pin="S"/>
<wire x1="518.16" y1="238.76" x2="525.78" y2="238.76" width="0.1524" layer="91"/>
<wire x1="525.78" y1="238.76" x2="525.78" y2="248.92" width="0.1524" layer="91"/>
<pinref part="VT4" gate="VT$1" pin="S"/>
<wire x1="538.48" y1="248.92" x2="530.86" y2="248.92" width="0.1524" layer="91"/>
<pinref part="R42" gate="G$1" pin="2"/>
<wire x1="530.86" y1="248.92" x2="525.78" y2="248.92" width="0.1524" layer="91"/>
<junction x="530.86" y="248.92"/>
<pinref part="VD1" gate="G$1" pin="C"/>
<wire x1="523.24" y1="248.92" x2="525.78" y2="248.92" width="0.1524" layer="91"/>
<junction x="525.78" y="248.92"/>
<wire x1="525.78" y1="238.76" x2="525.78" y2="231.14" width="0.1524" layer="91"/>
<junction x="525.78" y="238.76"/>
<wire x1="525.78" y1="231.14" x2="510.54" y2="231.14" width="0.1524" layer="91"/>
<wire x1="510.54" y1="231.14" x2="510.54" y2="215.9" width="0.1524" layer="91"/>
<pinref part="R39" gate="G$1" pin="1"/>
<wire x1="510.54" y1="215.9" x2="513.08" y2="215.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VBUS" class="1">
<segment>
<pinref part="VT3" gate="VT$1" pin="G"/>
<wire x1="515.62" y1="243.84" x2="515.62" y2="248.92" width="0.1524" layer="91"/>
<wire x1="515.62" y1="248.92" x2="452.12" y2="248.92" width="0.1524" layer="91"/>
<wire x1="452.12" y1="248.92" x2="452.12" y2="238.76" width="0.1524" layer="91"/>
<pinref part="R41" gate="G$1" pin="2"/>
<pinref part="R40" gate="G$1" pin="1"/>
<wire x1="452.12" y1="238.76" x2="452.12" y2="236.22" width="0.1524" layer="91"/>
<wire x1="457.2" y1="238.76" x2="452.12" y2="238.76" width="0.1524" layer="91"/>
<junction x="452.12" y="238.76"/>
<wire x1="452.12" y1="238.76" x2="441.96" y2="238.76" width="0.1524" layer="91"/>
<label x="441.96" y="238.76" size="1.778" layer="95"/>
<pinref part="VD1" gate="G$1" pin="A"/>
<wire x1="518.16" y1="248.92" x2="515.62" y2="248.92" width="0.1524" layer="91"/>
<junction x="515.62" y="248.92"/>
</segment>
<segment>
<wire x1="525.78" y1="226.06" x2="513.08" y2="226.06" width="0.1524" layer="91"/>
<label x="513.08" y="226.06" size="1.778" layer="95"/>
<pinref part="VT5" gate="G$1" pin="B"/>
</segment>
<segment>
<pinref part="XT1" gate="G$1" pin="VDD"/>
<wire x1="762" y1="231.14" x2="767.08" y2="231.14" width="0.1524" layer="91"/>
<wire x1="767.08" y1="231.14" x2="767.08" y2="236.22" width="0.1524" layer="91"/>
<pinref part="C25" gate="G$1" pin="1"/>
<wire x1="767.08" y1="236.22" x2="767.08" y2="251.46" width="0.1524" layer="91"/>
<wire x1="754.38" y1="248.92" x2="754.38" y2="251.46" width="0.1524" layer="91"/>
<wire x1="754.38" y1="251.46" x2="767.08" y2="251.46" width="0.1524" layer="91"/>
<wire x1="767.08" y1="236.22" x2="810.26" y2="236.22" width="0.1524" layer="91"/>
<label x="810.26" y="236.22" size="1.778" layer="95" rot="MR0"/>
<junction x="767.08" y="236.22"/>
<junction x="767.08" y="236.22"/>
<pinref part="C33" gate="G$1" pin="1"/>
<pinref part="DD4" gate="DD$1" pin="VBUS"/>
<wire x1="772.16" y1="226.06" x2="767.08" y2="226.06" width="0.1524" layer="91"/>
<wire x1="767.08" y1="226.06" x2="767.08" y2="220.98" width="0.1524" layer="91"/>
<wire x1="767.08" y1="226.06" x2="767.08" y2="231.14" width="0.1524" layer="91"/>
<junction x="767.08" y="226.06"/>
<junction x="767.08" y="231.14"/>
</segment>
<segment>
<wire x1="508" y1="147.32" x2="492.76" y2="147.32" width="0.1524" layer="91"/>
<label x="492.76" y="147.32" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA9"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="VT4" gate="VT$1" pin="G"/>
<pinref part="R42" gate="G$1" pin="1"/>
<wire x1="541.02" y1="243.84" x2="541.02" y2="238.76" width="0.1524" layer="91"/>
<wire x1="541.02" y1="238.76" x2="535.94" y2="238.76" width="0.1524" layer="91"/>
<pinref part="VD2" gate="G$1" pin="A"/>
<wire x1="535.94" y1="238.76" x2="530.86" y2="238.76" width="0.1524" layer="91"/>
<wire x1="541.02" y1="238.76" x2="543.56" y2="238.76" width="0.1524" layer="91"/>
<junction x="541.02" y="238.76"/>
<pinref part="VT5" gate="G$1" pin="C"/>
<wire x1="530.86" y1="231.14" x2="530.86" y2="238.76" width="0.1524" layer="91"/>
<junction x="530.86" y="238.76"/>
<pinref part="VT6" gate="G$1" pin="C"/>
<wire x1="535.94" y1="231.14" x2="535.94" y2="238.76" width="0.1524" layer="91"/>
<junction x="535.94" y="238.76"/>
</segment>
</net>
<net name="PWR_EN" class="0">
<segment>
<pinref part="VT6" gate="G$1" pin="B"/>
<wire x1="541.02" y1="226.06" x2="558.8" y2="226.06" width="0.1524" layer="91"/>
<label x="558.8" y="226.06" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<pinref part="DD2" gate=".1" pin="PB2"/>
<wire x1="551.18" y1="165.1" x2="533.4" y2="165.1" width="0.1524" layer="91"/>
<label x="551.18" y="165.1" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="R5" gate="G$1" pin="2"/>
<wire x1="591.82" y1="330.2" x2="594.36" y2="330.2" width="0.1524" layer="91"/>
<wire x1="594.36" y1="330.2" x2="594.36" y2="337.82" width="0.1524" layer="91"/>
<pinref part="X1" gate="X$1" pin="AGND"/>
<wire x1="594.36" y1="337.82" x2="596.9" y2="337.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="U_DM" class="0">
<segment>
<wire x1="508" y1="142.24" x2="492.76" y2="142.24" width="0.1524" layer="91"/>
<label x="492.76" y="142.24" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA11"/>
</segment>
<segment>
<wire x1="800.1" y1="223.52" x2="810.26" y2="223.52" width="0.1524" layer="91"/>
<label x="810.26" y="223.52" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD4" gate="DD$1" pin="IO2.1"/>
</segment>
</net>
<net name="U_DP" class="0">
<segment>
<wire x1="508" y1="139.7" x2="492.76" y2="139.7" width="0.1524" layer="91"/>
<label x="492.76" y="139.7" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA12"/>
</segment>
<segment>
<wire x1="800.1" y1="228.6" x2="810.26" y2="228.6" width="0.1524" layer="91"/>
<label x="810.26" y="228.6" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD4" gate="DD$1" pin="IO1.1"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="DD4" gate="DD$1" pin="IO2.2"/>
<wire x1="764.54" y1="223.52" x2="772.16" y2="223.52" width="0.1524" layer="91"/>
<pinref part="XT1" gate="G$1" pin="DM"/>
<wire x1="762" y1="228.6" x2="764.54" y2="226.06" width="0.1524" layer="91"/>
<wire x1="764.54" y1="226.06" x2="764.54" y2="223.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="MEMS_INT1" class="0">
<segment>
<pinref part="DD5" gate="G$1" pin="INT1"/>
<wire x1="657.86" y1="284.48" x2="680.72" y2="284.48" width="0.1524" layer="91"/>
<label x="657.86" y="284.48" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="551.18" y1="147.32" x2="533.4" y2="147.32" width="0.1524" layer="91"/>
<label x="551.18" y="147.32" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB9"/>
</segment>
</net>
<net name="MEMS_INT2" class="0">
<segment>
<pinref part="DD5" gate="G$1" pin="INT2"/>
<wire x1="657.86" y1="281.94" x2="680.72" y2="281.94" width="0.1524" layer="91"/>
<label x="657.86" y="281.94" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="551.18" y1="149.86" x2="533.4" y2="149.86" width="0.1524" layer="91"/>
<label x="551.18" y="149.86" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB8"/>
</segment>
</net>
<net name="SWDIO" class="0">
<segment>
<label x="683.26" y="233.68" size="1.778" layer="95"/>
<wire x1="718.82" y1="233.68" x2="683.26" y2="233.68" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="3"/>
</segment>
<segment>
<wire x1="508" y1="137.16" x2="492.76" y2="137.16" width="0.1524" layer="91"/>
<label x="492.76" y="137.16" size="1.778" layer="95"/>
<pinref part="DD2" gate=".1" pin="PA13"/>
</segment>
</net>
<net name="SWCLK" class="0">
<segment>
<label x="683.26" y="238.76" size="1.778" layer="95"/>
<wire x1="703.58" y1="238.76" x2="683.26" y2="238.76" width="0.1524" layer="91"/>
<pinref part="C36" gate="G$1" pin="2"/>
<wire x1="703.58" y1="238.76" x2="703.58" y2="241.3" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="1"/>
<wire x1="718.82" y1="238.76" x2="703.58" y2="238.76" width="0.1524" layer="91"/>
<junction x="703.58" y="238.76"/>
</segment>
<segment>
<label x="492.76" y="134.62" size="1.778" layer="95"/>
<wire x1="508" y1="134.62" x2="492.76" y2="134.62" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".1" pin="PA14"/>
</segment>
</net>
<net name="NRST" class="0">
<segment>
<wire x1="683.26" y1="231.14" x2="718.82" y2="231.14" width="0.1524" layer="91"/>
<label x="683.26" y="231.14" size="1.778" layer="95"/>
<pinref part="JP1" gate="G$1" pin="4"/>
</segment>
<segment>
<label x="563.88" y="114.3" size="1.778" layer="95"/>
<pinref part="C48" gate="G$1" pin="1"/>
<wire x1="571.5" y1="114.3" x2="571.5" y2="111.76" width="0.1524" layer="91"/>
<pinref part="R55" gate="G$1" pin="1"/>
<wire x1="563.88" y1="114.3" x2="571.5" y2="114.3" width="0.1524" layer="91"/>
<junction x="571.5" y="114.3"/>
<pinref part="DD2" gate=".3" pin="NRST"/>
<wire x1="586.74" y1="127" x2="581.66" y2="127" width="0.1524" layer="91"/>
<wire x1="581.66" y1="127" x2="581.66" y2="114.3" width="0.1524" layer="91"/>
<wire x1="581.66" y1="114.3" x2="571.5" y2="114.3" width="0.1524" layer="91"/>
</segment>
</net>
<net name="MEMS_SDA" class="0">
<segment>
<pinref part="DD5" gate="G$1" pin="SDA_SDI_SDO"/>
<wire x1="680.72" y1="289.56" x2="657.86" y2="289.56" width="0.1524" layer="91"/>
<label x="657.86" y="289.56" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="533.4" y1="152.4" x2="551.18" y2="152.4" width="0.1524" layer="91"/>
<label x="551.18" y="152.4" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB7"/>
</segment>
</net>
<net name="MEMS_SCL" class="0">
<segment>
<pinref part="DD5" gate="G$1" pin="SCL_SPC"/>
<wire x1="657.86" y1="287.02" x2="680.72" y2="287.02" width="0.1524" layer="91"/>
<label x="657.86" y="287.02" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="551.18" y1="154.94" x2="533.4" y2="154.94" width="0.1524" layer="91"/>
<label x="551.18" y="154.94" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB6"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="DA1" gate="G$1" pin="BYPASS"/>
<pinref part="C38" gate="G$1" pin="1"/>
<wire x1="619.76" y1="243.84" x2="622.3" y2="243.84" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="DA2" gate="G$1" pin="BYPASS"/>
<pinref part="C43" gate="G$1" pin="1"/>
<wire x1="619.76" y1="210.82" x2="622.3" y2="210.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="C49" gate="G$1" pin="+"/>
<wire x1="624.84" y1="104.14" x2="624.84" y2="101.6" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VCAP_2"/>
<wire x1="624.84" y1="104.14" x2="622.3" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="C50" gate="G$1" pin="+"/>
<wire x1="635" y1="106.68" x2="635" y2="104.14" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VCAP_1"/>
<wire x1="622.3" y1="106.68" x2="635" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="C63" gate="G$1" pin="+"/>
<wire x1="652.78" y1="127" x2="652.78" y2="124.46" width="0.1524" layer="91"/>
<wire x1="652.78" y1="124.46" x2="652.78" y2="121.92" width="0.1524" layer="91"/>
<wire x1="652.78" y1="127" x2="660.4" y2="127" width="0.1524" layer="91"/>
<pinref part="C65" gate="G$1" pin="1"/>
<wire x1="660.4" y1="127" x2="660.4" y2="121.92" width="0.1524" layer="91"/>
<pinref part="R57" gate="G$1" pin="1"/>
<junction x="660.4" y="127"/>
<pinref part="DD2" gate=".3" pin="VREF+"/>
<wire x1="622.3" y1="124.46" x2="652.78" y2="124.46" width="0.1524" layer="91"/>
<junction x="652.78" y="124.46"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="R57" gate="G$1" pin="2"/>
<wire x1="670.56" y1="106.68" x2="660.4" y2="106.68" width="0.1524" layer="91"/>
<pinref part="C64" gate="G$1" pin="+"/>
<wire x1="660.4" y1="106.68" x2="650.24" y2="106.68" width="0.1524" layer="91"/>
<wire x1="650.24" y1="106.68" x2="650.24" y2="104.14" width="0.1524" layer="91"/>
<wire x1="650.24" y1="106.68" x2="647.7" y2="106.68" width="0.1524" layer="91"/>
<junction x="650.24" y="106.68"/>
<pinref part="C66" gate="G$1" pin="1"/>
<wire x1="660.4" y1="104.14" x2="660.4" y2="106.68" width="0.1524" layer="91"/>
<junction x="660.4" y="106.68"/>
<wire x1="670.56" y1="127" x2="670.56" y2="106.68" width="0.1524" layer="91"/>
<junction x="670.56" y="106.68"/>
<pinref part="L1" gate="G$1" pin="P$2"/>
<wire x1="675.64" y1="109.22" x2="675.64" y2="106.68" width="0.1524" layer="91"/>
<wire x1="675.64" y1="106.68" x2="670.56" y2="106.68" width="0.1524" layer="91"/>
<pinref part="DD2" gate=".3" pin="VDDA"/>
<wire x1="622.3" y1="111.76" x2="647.7" y2="111.76" width="0.1524" layer="91"/>
<wire x1="647.7" y1="111.76" x2="647.7" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="ZQ2" gate="G$1" pin="P$1"/>
<wire x1="640.08" y1="167.64" x2="640.08" y2="170.18" width="0.1524" layer="91"/>
<wire x1="640.08" y1="170.18" x2="650.24" y2="170.18" width="0.1524" layer="91"/>
<pinref part="C69" gate="G$1" pin="1"/>
<pinref part="DD2" gate=".3" pin="PH0"/>
<wire x1="622.3" y1="170.18" x2="640.08" y2="170.18" width="0.1524" layer="91"/>
<junction x="640.08" y="170.18"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="ZQ2" gate="G$1" pin="P$2"/>
<pinref part="R59" gate="G$1" pin="2"/>
<wire x1="640.08" y1="160.02" x2="640.08" y2="157.48" width="0.1524" layer="91"/>
<pinref part="C68" gate="G$1" pin="1"/>
<wire x1="640.08" y1="157.48" x2="650.24" y2="157.48" width="0.1524" layer="91"/>
<junction x="640.08" y="157.48"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="M1" gate="M$1" pin="P$1"/>
<pinref part="VT2" gate="VT$1" pin="D"/>
</segment>
</net>
<net name="NVBTR" class="0">
<segment>
<pinref part="VT2" gate="VT$1" pin="G"/>
<wire x1="764.54" y1="180.34" x2="774.7" y2="180.34" width="0.1524" layer="91"/>
<wire x1="774.7" y1="180.34" x2="774.7" y2="185.42" width="0.1524" layer="91"/>
<pinref part="R8" gate="G$1" pin="2"/>
<wire x1="774.7" y1="185.42" x2="772.16" y2="185.42" width="0.1524" layer="91"/>
<wire x1="774.7" y1="185.42" x2="784.86" y2="185.42" width="0.1524" layer="91"/>
<junction x="774.7" y="185.42"/>
<label x="784.86" y="185.42" size="1.778" layer="95" rot="MR0"/>
</segment>
<segment>
<wire x1="533.4" y1="160.02" x2="551.18" y2="160.02" width="0.1524" layer="91"/>
<label x="551.18" y="160.02" size="1.778" layer="95" rot="MR0"/>
<pinref part="DD2" gate=".1" pin="PB4"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="R59" gate="G$1" pin="1"/>
<pinref part="DD2" gate=".3" pin="PH1"/>
<wire x1="629.92" y1="157.48" x2="622.3" y2="157.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="XT1" gate="G$1" pin="DP"/>
<wire x1="762" y1="226.06" x2="764.54" y2="228.6" width="0.1524" layer="91"/>
<pinref part="DD4" gate="DD$1" pin="IO1.2"/>
<wire x1="764.54" y1="228.6" x2="772.16" y2="228.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SWO" class="0">
<segment>
<pinref part="JP1" gate="G$1" pin="5"/>
<wire x1="718.82" y1="228.6" x2="683.26" y2="228.6" width="0.1524" layer="91"/>
<label x="683.26" y="228.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="DD2" gate=".1" pin="PB3"/>
<wire x1="533.4" y1="162.56" x2="551.18" y2="162.56" width="0.1524" layer="91"/>
<label x="551.18" y="162.56" size="1.778" layer="95" rot="MR0"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="104,1,756.92,355.6,D1,VDD1,+3V3,,,"/>
<approved hash="104,1,756.92,353.06,D1,VDD2,+3V3,,,"/>
<approved hash="104,1,756.92,347.98,D1,VSS,GND,,,"/>
<approved hash="104,1,502.92,302.26,DD1,VA,+2V5,,,"/>
<approved hash="104,1,502.92,299.72,DD1,VD,+2V5,,,"/>
<approved hash="104,1,502.92,289.56,DD1,VL,+3V3,,,"/>
<approved hash="104,1,502.92,287.02,DD1,DGND,GND,,,"/>
<approved hash="202,1,543.56,299.72,DD1,AIN1B,,,,"/>
<approved hash="202,1,543.56,302.26,DD1,AIN1A,,,,"/>
<approved hash="202,1,543.56,304.8,DD1,AIN2B,,,,"/>
<approved hash="202,1,543.56,307.34,DD1,AIN2A,,,,"/>
<approved hash="202,1,543.56,309.88,DD1,AIN3B,,,,"/>
<approved hash="202,1,543.56,312.42,DD1,AIN3A,,,,"/>
<approved hash="202,1,543.56,314.96,DD1,AIN4B,,,,"/>
<approved hash="202,1,543.56,317.5,DD1,AIN4A,,,,"/>
<approved hash="104,1,543.56,284.48,DD1,AGND,GND,,,"/>
<approved hash="104,1,502.92,284.48,DD1,GND/PAD,GND,,,"/>
<approved hash="104,1,678.18,347.98,X2,VDD,+3V3,,,"/>
<approved hash="104,1,678.18,330.2,X2,VSS,GND,,,"/>
<approved hash="104,1,678.18,320.04,X2,SH,GND,,,"/>
<approved hash="104,1,680.72,297.18,DD5,VDD_IO,+3V3,,,"/>
<approved hash="104,1,680.72,294.64,DD5,VDD,+3V3,,,"/>
<approved hash="103,1,680.72,292.1,DD5,RESERVED,+3V3,,,"/>
<approved hash="103,1,718.82,281.94,DD5,RESERVED,GND,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
