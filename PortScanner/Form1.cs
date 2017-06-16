using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
namespace PortScanner
{
    public partial class PortScanner : Form
    {
        [DllImport("Functionality.dll")]
        public static extern bool CHECK_SYNTAX([MarshalAs(UnmanagedType.LPStr)] string IPs, [MarshalAs(UnmanagedType.LPStr)] string ports, bool ScanForCommonPorts);
        [DllImport("Functionality.dll")]
        public static extern IntPtr TCP_SCAN([MarshalAs(UnmanagedType.LPStr)] string IPs, [MarshalAs(UnmanagedType.LPStr)] string ports, bool PingBeforeScan, bool ScanForCommonPorts,int grupare);
        [DllImport("Functionality.dll")]
        public static extern IntPtr ICMP_SCAN([MarshalAs(UnmanagedType.LPStr)] string IPs);
        [DllImport("Functionality.dll")]
        public static extern IntPtr ADV_ICMP_SCAN([MarshalAs(UnmanagedType.LPStr)] string IPs);
        [DllImport("Functionality.dll")]
        public static extern IntPtr UDP_SCAN([MarshalAs(UnmanagedType.LPStr)] string IPs, [MarshalAs(UnmanagedType.LPStr)] string ports, bool PingBeforeScan, bool ScanForCommonPorts, int grupare);

        public PortScanner()
        {
            InitializeComponent();
        }

        private void SCAN_Button_Click(object sender, EventArgs e)
        {
            Afisaj.Clear();
            string ips = IP_Box.Text;
            string ports = Port_Box.Text;
            bool ScanCommonPorts, PingBeforeScan;
            if (CommonPorts.Checked)
                ScanCommonPorts = true;
            else
                ScanCommonPorts = false;
            if (PingBefore.Checked)
                PingBeforeScan = true;
            else
                PingBeforeScan = false;
            int tip_grupare=0;
            if (Group_IP.Checked)
                tip_grupare = 0;
            else
                if (Group_Port.Checked)
                    tip_grupare = 1;
                else
                    MessageBox.Show("Va rugam selectati un tip de afisare a scanarii!!!");
            if (CHECK_SYNTAX(ips, ports, ScanCommonPorts) == false)
            {
                progressBar1.Maximum = 1;
                progressBar1.Step = 1;
                progressBar1.PerformStep();
                MessageBox.Show("Wrong IP(s) or Port Number(s)!");
            }
            if (TCP_Button.Checked) //TCP_SCAN
            {
                progressBar1.Refresh();
                progressBar1.Maximum = 1;
                progressBar1.Step = 1;
                IntPtr aux = TCP_SCAN(ips, ports, PingBeforeScan, ScanCommonPorts, tip_grupare);
                progressBar1.PerformStep();
                string s = Marshal.PtrToStringAnsi(aux);
                Afisaj.AppendText(s);
                progressBar1.PerformStep();
            }
            else
                if (ICMP_Button.Checked) //ICMP SCAN
                {
                    progressBar1.Refresh();
                    progressBar1.Maximum = 1;
                    progressBar1.Step = 1;
                    IntPtr aux = ICMP_SCAN(ips);
                    progressBar1.PerformStep();
                    string s = Marshal.PtrToStringAnsi(aux);
                    Afisaj.AppendText(s);
                    progressBar1.PerformStep();
                }
                else
                    if (ICMP2_Button.Checked) //ADV_ICMP SCAN multithread
                    {
                        progressBar1.Refresh();
                        progressBar1.Maximum = 1;
                        progressBar1.Step = 1;
                        IntPtr aux = ADV_ICMP_SCAN(ips);
                        progressBar1.PerformStep();
                        string s = Marshal.PtrToStringAnsi(aux);
                        Afisaj.AppendText(s);
                        progressBar1.PerformStep();
                    }
                    else
                        if (UDP_Button.Checked)  //UDP SCAN
                        {
                            progressBar1.Refresh();
                            progressBar1.Maximum = 1;
                            progressBar1.Step = 1;
                            IntPtr aux = UDP_SCAN(ips, ports, PingBeforeScan, ScanCommonPorts, tip_grupare);
                            progressBar1.PerformStep();
                            string s = Marshal.PtrToStringAnsi(aux);
                            Afisaj.AppendText(s);
                            progressBar1.PerformStep();
                        }
                        else
                            MessageBox.Show("Please Select a Scan Type");
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void AboutMenu_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Aceasta aplicatie a fost dezvoltata de Jurj Danut si Medvei Mirabela cu scopul de a detecta porturile deschise ale unui PC. Toate drepturile sunt rezervate!");
        }

        private void TCP_Button_CheckedChanged(object sender, EventArgs e)
        {
            Port_Box.Show();
            CLR_Port_Button.Show();
            CommonPorts.Show();
            PingBefore.Show();
        }

        private void ICMP_Button_CheckedChanged(object sender, EventArgs e)
        {
            Port_Box.Hide();
            CLR_Port_Button.Hide();
            CommonPorts.Hide();
            PingBefore.Hide();
        }

        private void ICMP2_Button_CheckedChanged(object sender, EventArgs e)
        {
            Port_Box.Hide();
            CLR_Port_Button.Hide();
            CommonPorts.Hide();
            PingBefore.Hide();
        }

        private void UDP_Button_CheckedChanged(object sender, EventArgs e)
        {
            Port_Box.Show();
            CLR_Port_Button.Show();
            CommonPorts.Show();
            PingBefore.Show();
        }

        private void Afisaj_TextChanged(object sender, EventArgs e)
        {

        }

        private void CLR_IP_Button_Click(object sender, EventArgs e)
        {
            IP_Box.Clear();
        }

        private void CLR_Port_Button_Click(object sender, EventArgs e)
        {
            Port_Box.Clear();
        }






        private void CommonPorts_CheckedChanged(object sender, EventArgs e)
        {
            if (CommonPorts.Checked)
            {
                CLR_Port_Button.Hide();
                Port_Box.Hide();
            }
            else
            {
                CLR_Port_Button.Show();
                Port_Box.Show();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            
        }
        private void textBox1_Click(object sender, EventArgs e)
        {
           
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }



        private void PingBefore_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void aToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void aToolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void asToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void HelpButton_Click(object sender, EventArgs e)
        {

        }

        private void Group_IP_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }


    }
}
