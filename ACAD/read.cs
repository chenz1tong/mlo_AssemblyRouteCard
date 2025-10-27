using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ACadSharp;
using ACadSharp.Entities;
using ACadSharp.IO;
using ACadSharp.IO.DWG;
using ACadSharp.Tables;
using CSMath;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
namespace ACAD
{
    public class Read
    {
        public struct ViewPortInfo
        {
            public double centerX;
            public double centerY;
            public double width;
            public double height;
            //ViewPortInfo()
            //{

            //}
        }
        public struct MTextInfo
        {
            public double left;
            public double right;
            public double top;
            public double bottom;
            //public String text;
            public String key;
        }
        public struct Point2D
        {
            public double x;
            public double y;
        }
        public struct DWGInfo
        {
            public MTextInfo CustomerDwgSn;
            public MTextInfo CustomerVersion;
            public MTextInfo ObjectSn;
            public MTextInfo partName;
            public MTextInfo Material;
            public MTextInfo DwgVersion;
            public MTextInfo Version;
            public MTextInfo CA;
            public MTextInfo projectName;
        }
        public ViewPortInfo m_vport;
        public string m_all;
        string temp = "";
        string tempR = "";
        double tempDiameter = 0;
        int CAIndex = 0;
        int RIndex = 0;
        double s1;
        double s2;
        double singleRLeader = 0;
        Point2D s1Center;
        Point2D s2Center;
        double crossPoint1 = 0;
        double crossPoint2 = 0;
        Arc a1 = new Arc();
        Arc a2 = new Arc();
        double a1R = 0;
        double a2R = 0;
        double arc1StartX = 0;
        double arc2StartX = 0;
        Dictionary<Point2D, string> R = new Dictionary<Point2D, string>();

        public DWGInfo m_info;
		bool judgeVport = false;
		public Dictionary<string, string> _map=new Dictionary<string, string>();
        public bool ReadS1S2(string path)
        {

            string filePath = @path;
            // 使用 DwgReader 读取 DWG 文件
            CadDocument document;

            //try
            //{
                //= DwgReader.Read(filePath);
                bool res = TryReadDwg(filePath, out document);
                if (!res)
                    return false;
                
            //}catch(Exception ex)
            //{

            //}

            s1Center.x = 0;
            s1Center.y = 0;
            s2Center.x = 0;
            s2Center.y = 0;
            string Rtext;

            foreach (var entity in document.Entities)
            {
                if ((entity is Viewport viewport) && (!judgeVport))
                {
                    m_vport.centerX = viewport.Center.X;
                    m_vport.centerY = viewport.Center.Y;
                    m_vport.width = viewport.Width;
                    m_vport.height = viewport.Height;
                    judgeVport = true;
                }
            }
            foreach (var entity in document.Entities)
            {
                if (entity is MText mText && judgeVport)
                {


                    if (mText.InsertPoint.X > (m_vport.centerX - m_vport.width / 2) && mText.InsertPoint.X <( m_vport.centerX + m_vport.width / 2) &&
mText.InsertPoint.Y > (m_vport.centerY - m_vport.height / 2) && mText.InsertPoint.Y <( m_vport.centerY + m_vport.height / 2))
                    {
                        //System.Diagnostics.Trace.WriteLine("vp width LOW is " + (m_vport.centerX - m_vport.width / 2));
                        //System.Diagnostics.Trace.WriteLine("vp width HIGH is " + (m_vport.centerX + m_vport.width / 2));
                        //System.Diagnostics.Trace.WriteLine("vp hei LOW is " + (m_vport.centerY - m_vport.height / 2));
                        //System.Diagnostics.Trace.WriteLine("vp hei high is " + (m_vport.centerY + m_vport.height / 2));

                            System.Diagnostics.Trace.WriteLine("s1 length " + (mText.Value.Length));
                            System.Diagnostics.Trace.WriteLine("testt " + mText.Value.Substring(mText.Value.IndexOf(";") + 1, mText.Value.Length - 1 - mText.Value.IndexOf(";")));


                        if (mText.Value == "S1" || mText.Value.Substring(mText.Value.IndexOf(";") + 1, mText.Value.Length - 2 - mText.Value.IndexOf(";")) == "S1")
                        { 
                            s1 = mText.InsertPoint.X;
                            System.Diagnostics.Trace.WriteLine("s1 vall " + (mText.Value));

                        }
                        else if (mText.Value == "S2" || mText.Value.Substring(mText.Value.IndexOf(";") + 1, mText.Value.Length - 2 - mText.Value.IndexOf(";")) == "S2")
                        {
                            s2 = mText.InsertPoint.X;
                            System.Diagnostics.Trace.WriteLine("s2 vall " + (mText.Value));
                        }

                    }
                }
                if (entity is Dimension dim && judgeVport)
                {
                    if (!judgeIsInVP(dim))
                        continue;
                    System.Diagnostics.Trace.WriteLine("dimension is" + dim.Text);

                    if (entity is DimensionRadius radius)
                    {
                        System.Diagnostics.Trace.WriteLine("radius is" + radius.Text);
                        if (RIndex == 0)
                        {
                            System.Diagnostics.Trace.WriteLine("text is" + radius.Text);

                            int idx = radius.Text.IndexOf("%");
                            if (idx <= 0)
                                tempR = radius.Text;
                            else
                                tempR = radius.Text.Substring(0, idx);
                            System.Diagnostics.Trace.WriteLine("tempr is" + tempR);
                            tempR = tempR.Replace("R", "");
                            s1Center.x = radius.DefinitionPoint.X;
                            s1Center.y = radius.DefinitionPoint.Y;
                            System.Diagnostics.Trace.WriteLine("tempr  center is" + s1Center);
                            R.Add(s1Center, tempR);
                        }
                        else
                        {
                            System.Diagnostics.Trace.WriteLine("text is" + radius.Text);
                            string tempR2;
                            int idx2 = radius.Text.IndexOf("%");
                            if (idx2 <= 0)
                                tempR2 = radius.Text;
                            else
                                tempR2 = radius.Text.Substring(0, idx2);
                            Rtext = tempR2.Replace("R", "");
                            System.Diagnostics.Trace.WriteLine("R is" + radius.Text);
                            s2Center.x = radius.DefinitionPoint.X;
                            s2Center.y = radius.DefinitionPoint.Y;
                            System.Diagnostics.Trace.WriteLine("tempr 2 center is" + s2Center);
                            R.Add(s2Center, Rtext);
                            //_map.Add("R", Rtext);

                        };

                        RIndex++;
                    }
                }
                }
            return true;
        }
         public bool ReadDxf(string path)
        {
            ReadJson();
            bool ress=ReadS1S2(path);
            if (!ress)
                return false;
            //ReadS1S2(path);
            //System.Diagnostics.Trace.WriteLine("s1 is " + (s1));
            System.Diagnostics.Trace.WriteLine("s2 is " + (s2));
            string filePath = @path;
            try
            {
                byte[] header = new byte[6];
                using (var fs = File.OpenRead(filePath))
                    fs.Read(header, 0, 6);

                string version = System.Text.Encoding.ASCII.GetString(header);
                if (!version.StartsWith("AC"))
                {
                    System.Diagnostics.Trace.WriteLine("acac ");
                    //Console.WriteLine("不是有效 DWG 文件。");
                    return false;
                }
                System.Diagnostics.Trace.WriteLine("guoguo" );
                CadDocument document;/*= DwgReader.Read(filePath);*/
                // 使用 DwgReader 读取 DWG 文件
                bool res=TryReadDwg(filePath, out document);
                if (!res)
                    return false;
                CAIndex = 0;
                foreach (var entity in document.Entities)
                {
                    //if ((entity is Viewport viewport) && (!judgeVport))
                    //{
                    //    m_vport.centerX = viewport.Center.X;
                    //    m_vport.centerY = viewport.Center.Y;
                    //    m_vport.width = viewport.Width;
                    //    m_vport.height = viewport.Height;
                    //    judgeVport = true;
                    //}
                    if (entity is MText mText && judgeVport)
                    {
                        setItems(mText, m_info.partName);
                        setItems(mText, m_info.CustomerVersion);
                        setItems(mText, m_info.CustomerDwgSn);
                        setItems(mText, m_info.DwgVersion);
                        System.Diagnostics.Trace.WriteLine("start4");

                        setItems(mText, m_info.CA);
                        setItems(mText, m_info.Material);
                        setItems(mText, m_info.projectName);
                        setItems(mText, m_info.ObjectSn);

                        System.Diagnostics.Trace.WriteLine($"MText: X={mText.InsertPoint.X}, Y={mText.InsertPoint.Y}, Text={mText.Value}, Height={mText.Height}");
                    }
                    if (entity is Leader leader && judgeVport)
                    {
                        System.Diagnostics.Trace.WriteLine($"S1={s1}, S2={s2}");

                        if (leader.Vertices.Count() == 2 && (Math.Abs(leader.Vertices[0].X - s1) < 10 || Math.Abs(leader.Vertices[0].X - s2) < 10))
                        {
                            singleRLeader = leader.Vertices[0].X;
                            System.Diagnostics.Trace.WriteLine($"leader: leader={singleRLeader}");

                        }
                    }
                    if (entity is Arc arc && judgeVport)
                    {
                        if (arc.Center.X > (m_vport.centerX - m_vport.width / 2) && arc.Center.X < m_vport.centerX + m_vport.width / 2 &&
arc.Center.Y > m_vport.centerY - m_vport.height / 2 && arc.Center.Y < m_vport.centerY + m_vport.height / 2)
                        {
                            System.Diagnostics.Trace.WriteLine("ARC is" + arc.Center);
                            System.Diagnostics.Trace.WriteLine("ARC11 s1Center x is" + s1Center.x);
                            System.Diagnostics.Trace.WriteLine("ARC11 s1Center y is" + s1Center.y);
                            System.Diagnostics.Trace.WriteLine("ARC11 s2Center x is" + s2Center.x);
                            System.Diagnostics.Trace.WriteLine("ARC11 s2Center y is" + s2Center.y);
                            if (RIndex == 1)
                            {
                                arc2StartX = singleRLeader;
                            }
                            if (Math.Round(arc.Center.X, 4) == Math.Round(s1Center.x, 4) && Math.Round(arc.Center.Y, 4) == Math.Round(s1Center.y, 4))
                            {
                                System.Diagnostics.Trace.WriteLine("cos 1 is" + arc.Radius * Math.Cos(arc.StartAngle));
                                System.Diagnostics.Trace.WriteLine("startangle 1 is" + (arc.StartAngle));
                                a1 = arc;
                                a1R = arc.Radius;

                                if (s1Center.x < s1)
                                {
                                    arc1StartX = s1Center.x + arc.Radius /** Math.Cos(arc.StartAngle)*/;
                                    //arc1StartY = s1Center.x + arc.Radius * Math.Cos(arc.StartAngle);
                                }
                                else
                                {
                                    arc1StartX = s1Center.x - arc.Radius /** Math.Cos(180 - arc.StartAngle)*/;

                                }
                            }

                            if (Math.Round(arc.Center.X, 4) == Math.Round(s2Center.x, 4) && Math.Round(arc.Center.Y, 4) == Math.Round(s2Center.y, 4))
                            {
                                System.Diagnostics.Trace.WriteLine("cos 2 is" + arc.Radius * Math.Cos(arc.StartAngle));
                                System.Diagnostics.Trace.WriteLine("cos 2 radius is" + arc.Radius);
                                System.Diagnostics.Trace.WriteLine("startangle 2  start is" + (arc.StartAngle));
                                System.Diagnostics.Trace.WriteLine("startangle 2  end is" + (arc.EndAngle));

                                a2 = arc;
                                a2R = arc.Radius;

                                if (s2Center.x < s1)
                                {

                                    arc2StartX = s1Center.x + arc.Radius /** Math.Cos(arc.StartAngle)*/;
                                }
                                else
                                {
                                    System.Diagnostics.Trace.WriteLine("ARC11 is" + arc.Center);
                                    System.Diagnostics.Trace.WriteLine("ARC2 radius is" + arc.Radius);

                                    arc2StartX = s2Center.x - arc.Radius /** Math.Cos(180 - arc.StartAngle)*/;
                                    System.Diagnostics.Trace.WriteLine("cos 2 center is" + arc2StartX);

                                }
                            }
                            System.Diagnostics.Trace.WriteLine("ARC11 is" + arc.Center);
                            System.Diagnostics.Trace.WriteLine("s1center is" + s1Center.x);
                            //System.Diagnostics.Trace.WriteLine("s1 is" + s1);
                            System.Diagnostics.Trace.WriteLine("rr1 is" + a1.Radius);

                            //if (arc1StartX == 0 || arc2StartX == 0)
                            //    continue;

                        }
                    }
                }
            if (RIndex > 0)
                judgeRVal();
            else
                _map.Add("R", "\u221E,\u221E");

                foreach (var entity in document.Entities)
                {
                    if (entity is Dimension dim && judgeVport)
                    {
                        System.Diagnostics.Trace.WriteLine("dim type is" + dim.GetType().FullName);

                        if (!judgeIsInVP(dim))
                            continue;
                        System.Diagnostics.Trace.WriteLine("dimension is" + dim.Text);
                        if (entity is DimensionLinear d)
                        {
                            System.Diagnostics.Trace.WriteLine("d11 is" + d.Text);
                            System.Diagnostics.Trace.WriteLine("d first is" + Math.Round(d.FirstPoint.X, 4));
                            System.Diagnostics.Trace.WriteLine("d s1 is" + Math.Round(s1, 4));
                            System.Diagnostics.Trace.WriteLine("d second is" + Math.Round(d.SecondPoint.X, 4));
                            System.Diagnostics.Trace.WriteLine("d s2 is" + Math.Round(s2, 4));
                            System.Diagnostics.Trace.WriteLine("Math.Abs(d.FirstPoint.X-s1) is" + Math.Abs(d.FirstPoint.X - s1));
                            System.Diagnostics.Trace.WriteLine("rindex is" + RIndex);
                            System.Diagnostics.Trace.WriteLine("crossp1 is" + crossPoint1);
                            System.Diagnostics.Trace.WriteLine("crossp2 is" + crossPoint2);
                            if (d.Text.Contains("%%C") && d.Text.IndexOf("C") == 2)
                            {
                                //diameter
                                System.Diagnostics.Trace.WriteLine("diameter is" + d.Text);
                                string str0 = d.Text.Substring(d.Text.IndexOf("C") + 1);
                                string maxDiameter = setDiameter(str0);
                                System.Diagnostics.Trace.WriteLine("res is" + maxDiameter);

                                if (maxDiameter != "")
                                    _map.Add("diameter", maxDiameter);
                            }
                            //System.Diagnostics.Trace.WriteLine("res is" + maxDiameter);

                            else if (((RIndex > 1) && ((Math.Round(d.FirstPoint.X, 4) == Math.Round(crossPoint1, 4) && Math.Round(d.SecondPoint.X, 4) == Math.Round(crossPoint2, 4)) ||
                                (Math.Round(d.FirstPoint.X, 4) == Math.Round(crossPoint2, 4) && Math.Round(d.SecondPoint.X, 4) == Math.Round(crossPoint1, 4)))) || ((RIndex == 0) &&
                                ((Math.Abs(d.FirstPoint.X - s1) < 7 && Math.Abs(d.SecondPoint.X - s2) < 7) || (Math.Abs(d.FirstPoint.X - s2) < 7 && Math.Abs(d.SecondPoint.X - s1) < 7))))
                            {

                                System.Diagnostics.Trace.WriteLine("thick is" + d.Text);
                                System.Diagnostics.Trace.WriteLine("d first is" + d.FirstPoint.X);
                                System.Diagnostics.Trace.WriteLine("d second is" + d.SecondPoint.X);
                                System.Diagnostics.Trace.WriteLine("d DEF is" + d.DefinitionPoint.X);
                                //System.Diagnostics.Trace.WriteLine("d insert is" + d.PO);
                                string str = d.Text.Replace("%%P", ",");
                                _map.Add("centerThick", str);
                            }
                        }
                    }
                }
                return true;
          }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.Message);

                System.Diagnostics.Trace.WriteLine("Error reading DWG file: {0}" + ex.Message);
                return false;
            }
}

        public static bool TryReadDwg(string filePath, out CadDocument document)
        {
            document = null;

            if (!File.Exists(filePath))
                return false;

            FileStream fs = null;
            DwgReader reader = null;

            try
            {
                fs = new FileStream(filePath, FileMode.Open, FileAccess.Read);
                reader = new DwgReader(fs);   // 注意：用流构造！

                document = reader.Read();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"读取 DWG 出错：{ex.GetType().Name} - {ex.Message}");
                return false;
            }
            finally
            {
                // 避免 Dispose() 中再次抛异常
                try { reader?.Dispose(); } catch { }
                try { fs?.Dispose(); } catch { }
            }
        }
        private void judgeRVal()
        {
            string RRes;
            string RLeft="";
            string RRight;
            System.Diagnostics.Trace.WriteLine("arc1StartX 1 is" + (arc1StartX));
            System.Diagnostics.Trace.WriteLine("arc2StartX 1 is" + (arc2StartX));

            if (arc1StartX < arc2StartX)
            {
                if (s1Center.x < s1)
                {
                    RLeft = "-" + R[s1Center];
                    crossPoint1 = s1Center.x + a1R;
                }
                else
                {
                    RLeft = "+" + R[s1Center];
                    crossPoint1 = s1Center.x - a1R;

                }
                if (s2Center.x < s2)
                {
                    if (!R.ContainsKey(s2Center))
                        RRight = "\u221E";
                    else
                        RRight = "+" + R[s2Center];
                    crossPoint2 = s2Center.x + a2R;
                }
                else
                {
                    if (!R.ContainsKey(s2Center))
                        RRight = "\u221E";
                    else
                        RRight = "-" + R[s2Center];
                    crossPoint2 = s2Center.x - a2R;

                }

            }
            else
            {
                if (s1Center.x < s2)
                {
                    RRight = "+" + R[s1Center];
                    crossPoint1 = s1Center.x + a1R;

                }
                else
                {
                    RRight = "-" + R[s1Center];
                    crossPoint1 = s1Center.x - a1R;

                }
                if (s2Center.x < s1)
                {
                    if (!R.ContainsKey(s2Center))
                        RLeft = "\u221E";
                    else
                        RLeft = "-" + R[s2Center];
                    crossPoint2 = s2Center.x + a2R;

                }
                else
                {
                    if (!R.ContainsKey(s2Center))
                        RLeft = "\u221E";
                    else
                        RLeft = "+" + R[s2Center];
                    crossPoint2 = s2Center.x - a2R;

                }
            }
            System.Diagnostics.Trace.WriteLine("cross1 2 is" + crossPoint1 + " 2 " + crossPoint2);

            RRes = "R1:" + RLeft + "," + "R2:" + RRight;

            System.Diagnostics.Trace.WriteLine("R is" + RRes);

            _map.Add("R", RRes);
        }
        private string setDiameter(string text)
        {
            //string tempDiameter, add, sub;
            if (text.Contains("%%P"))
            {
                int idx1 = text.IndexOf("P");
                string tempD = text.Substring(0, idx1 - 2);
                System.Diagnostics.Trace.WriteLine("dia is" + tempD);
                string add1 = "+" + text.Substring(idx1 + 1);
                string sub1 = "-" + text.Substring(idx1 + 1);
                System.Diagnostics.Trace.WriteLine("diameter same is" + tempD+add1+sub1);

                return "\u03A6" + tempD +","+ add1 +"/"+ sub1;
            }
            text = text.Remove(text.Length - 2);
            int idx = text.IndexOf("{");
            string str=text.Substring(0,idx);
            System.Diagnostics.Trace.WriteLine("tempDiameter str is" + str);

            double num;
            double.TryParse(str, out num);
            if (num < tempDiameter)
                return "";
                tempDiameter = num;
            System.Diagnostics.Trace.WriteLine("tempDiameter is" + tempDiameter);

            int idx2 = text.IndexOf("+");

            int idx3 = text.IndexOf("^");
            System.Diagnostics.Trace.WriteLine("text is" + text);

            string add = text.Substring(idx2, 2 );

            string sub = text.Substring( idx3 + 1);
            return "\u03A6"+tempDiameter + "," + add + "/" + sub;
        }
        private bool judgeIsInVP(Dimension m)
        {
            System.Diagnostics.Trace.WriteLine($"dim X{m.InsertionPoint.X}");
            System.Diagnostics.Trace.WriteLine($"dim text{m.Text}");
            System.Diagnostics.Trace.WriteLine($"dim definition X{m.DefinitionPoint.X}");
            System.Diagnostics.Trace.WriteLine($"dim definition Y{m.DefinitionPoint.Y}");
            System.Diagnostics.Trace.WriteLine($"dim TextMiddlePoint X{m.TextMiddlePoint.X}");
            //System.Diagnostics.Trace.WriteLine($"dim attach X{m.AttachmentPoint.X}");
            System.Diagnostics.Trace.WriteLine($"vp width{m_vport.width}");
            //System.Diagnostics.Trace.WriteLine($"dim X{m.InsertionPoint.X}");

            if (m.TextMiddlePoint.X > (m_vport.centerX - m_vport.width/2) && m.TextMiddlePoint.X < m_vport.centerX + m_vport.width/2 &&
m.TextMiddlePoint.Y > m_vport.centerY - m_vport.height/2 && m.TextMiddlePoint.Y < m_vport.centerY + m_vport.height / 2)
            {
                return true;
            }
            return false;
        }
        private void setItems(MText mText, MTextInfo item)
        {
            System.Diagnostics.Trace.WriteLine("setItem");
            try
            {
                if (mText.InsertPoint.X > (m_vport.centerX + item.left) && mText.InsertPoint.X < m_vport.centerX + item.right &&
    mText.InsertPoint.Y > m_vport.centerY + item.bottom && mText.InsertPoint.Y < m_vport.centerY + item.top)
			    {
				    string str = mText.Value;
                    if (str.Contains("图号"))
                        return;
                    else if (item.key == "CA")
                    {

                        switch (CAIndex)
                        {
                            case 0:temp = str; break;
                            case 1:if (temp.Contains("S1:"))
                                {
                                    temp=temp.Substring(3);
                                    str = str.Substring(3);
                                    str = temp + "," + str;
                                }
                                else if (temp.Contains("S2:")) {
                                    temp=temp.Substring(3);
                                    str=str.Substring(3);
                                    str = str + "," + temp;

                                };
                                break;
                            default:break;
                        }
                        CAIndex++;
                        System.Diagnostics.Trace.WriteLine("CA Val:"+str);
                        System.Diagnostics.Trace.WriteLine("CA index:"+CAIndex);
                        //if (str.Contains("%%C"))
                        //{
                        //    str=str.Replace("%%C", "\u00D8");
                        //    System.Diagnostics.Trace.WriteLine("CA%C Val:" + str);

                        //}
                        if (CAIndex == 1)
                        {
                            str += "," + "\u221E";
                            _map.Add(item.key, str);
                        }
                        else
                        {
                            _map[item.key] = str;
                        }

                        System.Diagnostics.Trace.WriteLine($"MText: key={item.key}, val={str}");
                        return;
                    }
                    else if(item.key== "Material")
                    {

                        if (str.Contains("\\P"))
                        {
                            int end = str.IndexOf("\\P");
                            str = str.Substring(0, end );
                        }
                        if (str.Contains("{"))
                        {
                            str = str.Substring(0, str.IndexOf("{"));
                        }
                    }

                    else if (str.Contains(";"))
                    {
                        int startIdx = str.IndexOf(";");

                        int endIdx = str.IndexOf("}", startIdx);
                        int Idx = str.IndexOf("}");
                        str = str.Substring(startIdx+1, endIdx - startIdx-1)+str.Substring(Idx+1);

                    }

                    _map.Add(item.key, str);
                    System.Diagnostics.Trace.WriteLine($"MText: key={item.key}, val={str}");

                    //m_all.Append(item.key);
                }
            }catch(Exception e)
            {
                System.Diagnostics.Trace.WriteLine(e.Message);
                //return false;
            }

        }

            public void ReadJson()
            {
            string JsonPath = @"D:\\mlo\\code\\AssemblyRouteCard\\src\\config\\relativeInfoPosInViewport.json";
            System.Diagnostics.Trace.WriteLine("111st");

            string jsonString = File.ReadAllText(JsonPath);
            System.Diagnostics.Trace.WriteLine(jsonString);

            JObject jsonObject = JObject.Parse(jsonString);
            m_info.Material.key = "Material";
            m_info.Material.left = (double)jsonObject["Material"]["left"];
            m_info.Material.right = (double)jsonObject["Material"]["right"];
            m_info.Material.top = (double)jsonObject["Material"]["top"];
            m_info.Material.bottom = (double)jsonObject["Material"]["bottom"];
            m_info.ObjectSn.key = "ObjectSN";
            m_info.ObjectSn.left = (double)jsonObject["ObjectSn"]["left"];
            m_info.ObjectSn.right = (double)jsonObject["ObjectSn"]["right"];
            m_info.ObjectSn.top = (double)jsonObject["ObjectSn"]["top"];
            m_info.ObjectSn.bottom = (double)jsonObject["ObjectSn"]["bottom"];
            m_info.CustomerDwgSn.key = "CustomerDwgSn";

            m_info.CustomerDwgSn.left = (double)jsonObject["CustomerDwgSn"]["left"];
            m_info.CustomerDwgSn.right = (double)jsonObject["CustomerDwgSn"]["right"];
            m_info.CustomerDwgSn.top = (double)jsonObject["CustomerDwgSn"]["top"];
            m_info.CustomerDwgSn.bottom = (double)jsonObject["CustomerDwgSn"]["bottom"];
            m_info.CustomerVersion.key = "CustomVersion";

            m_info.CustomerVersion.left = (double)jsonObject["CustomerVersion"]["left"];
            m_info.CustomerVersion.right = (double)jsonObject["CustomerVersion"]["right"];
            m_info.CustomerVersion.top = (double)jsonObject["CustomerVersion"]["top"];
            m_info.CustomerVersion.bottom = (double)jsonObject["CustomerVersion"]["bottom"];
            m_info.DwgVersion.key = "DwgVersion";

            m_info.DwgVersion.left = (double)jsonObject["DwgVersion"]["left"];
            m_info.DwgVersion.right = (double)jsonObject["DwgVersion"]["right"];
            m_info.DwgVersion.top = (double)jsonObject["DwgVersion"]["top"];
            m_info.DwgVersion.bottom = (double)jsonObject["DwgVersion"]["bottom"];
            m_info.partName.key = "PartName";

            m_info.partName.left = (double)jsonObject["PartName"]["left"];
            m_info.partName.right = (double)jsonObject["PartName"]["right"];
            m_info.partName.top = (double)jsonObject["PartName"]["top"];
            m_info.partName.bottom = (double)jsonObject["PartName"]["bottom"];
            m_info.CA.key = "CA";

            m_info.CA.left = (double)jsonObject["CA"]["left"];
            m_info.CA.right = (double)jsonObject["CA"]["right"];
            m_info.CA.top = (double)jsonObject["CA"]["top"];
            m_info.CA.bottom = (double)jsonObject["CA"]["bottom"];
            m_info.projectName.key = "ProjectName";

            m_info.projectName.left = (double)jsonObject["projectName"]["left"];
            m_info.projectName.right = (double)jsonObject["projectName"]["right"];
            m_info.projectName.top = (double)jsonObject["projectName"]["top"];
            m_info.projectName.bottom = (double)jsonObject["projectName"]["bottom"];
            System.Diagnostics.Trace.WriteLine($"project X={m_info.projectName.bottom}");
            }
        void getDimensionRadiusText()
        {

        }
            public Dictionary<string, string> getInfo()
        {
            return _map;
        }
        //public string getInfoSTL()
        //{
        //    return 
        //}
        private static void OnNotification(object sender, NotificationEventArgs e)
        {
            Console.WriteLine(e.Message);
        }
    }

}
