namespace PortScanner
{
    partial class PortScanner
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PortScanner));
            this.Afisaj = new System.Windows.Forms.RichTextBox();
            this.SCAN_Button = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.aToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.asToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.HelpButton = new System.Windows.Forms.ToolStripMenuItem();
            this.AboutMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.IP_Box = new System.Windows.Forms.TextBox();
            this.Port_Box = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.TCP_Button = new System.Windows.Forms.RadioButton();
            this.ICMP_Button = new System.Windows.Forms.RadioButton();
            this.UDP_Button = new System.Windows.Forms.RadioButton();
            this.ICMP2_Button = new System.Windows.Forms.RadioButton();
            this.PingBefore = new System.Windows.Forms.CheckBox();
            this.CommonPorts = new System.Windows.Forms.CheckBox();
            this.CLR_IP_Button = new System.Windows.Forms.Button();
            this.CLR_Port_Button = new System.Windows.Forms.Button();
            this.Group_IP = new System.Windows.Forms.CheckBox();
            this.Group_Port = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Afisaj
            // 
            this.Afisaj.BackColor = System.Drawing.SystemColors.Window;
            this.Afisaj.ForeColor = System.Drawing.Color.Red;
            this.Afisaj.Location = new System.Drawing.Point(605, 107);
            this.Afisaj.Name = "Afisaj";
            this.Afisaj.ReadOnly = true;
            this.Afisaj.Size = new System.Drawing.Size(284, 422);
            this.Afisaj.TabIndex = 0;
            this.Afisaj.Text = "";
            this.Afisaj.TextChanged += new System.EventHandler(this.Afisaj_TextChanged);
            // 
            // SCAN_Button
            // 
            this.SCAN_Button.Location = new System.Drawing.Point(79, 53);
            this.SCAN_Button.Name = "SCAN_Button";
            this.SCAN_Button.Size = new System.Drawing.Size(132, 52);
            this.SCAN_Button.TabIndex = 1;
            this.SCAN_Button.Text = "SCAN";
            this.SCAN_Button.UseVisualStyleBackColor = true;
            this.SCAN_Button.Click += new System.EventHandler(this.SCAN_Button_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.RosyBrown;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.HelpButton});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(900, 28);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aToolStripMenuItem,
            this.aToolStripMenuItem1,
            this.asToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(58, 24);
            this.toolStripMenuItem1.Text = "Menu";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // aToolStripMenuItem
            // 
            this.aToolStripMenuItem.Name = "aToolStripMenuItem";
            this.aToolStripMenuItem.Size = new System.Drawing.Size(92, 24);
            this.aToolStripMenuItem.Text = "a";
            this.aToolStripMenuItem.Click += new System.EventHandler(this.aToolStripMenuItem_Click);
            // 
            // aToolStripMenuItem1
            // 
            this.aToolStripMenuItem1.Name = "aToolStripMenuItem1";
            this.aToolStripMenuItem1.Size = new System.Drawing.Size(92, 24);
            this.aToolStripMenuItem1.Text = "a";
            this.aToolStripMenuItem1.Click += new System.EventHandler(this.aToolStripMenuItem1_Click);
            // 
            // asToolStripMenuItem
            // 
            this.asToolStripMenuItem.Name = "asToolStripMenuItem";
            this.asToolStripMenuItem.Size = new System.Drawing.Size(92, 24);
            this.asToolStripMenuItem.Text = "as";
            this.asToolStripMenuItem.Click += new System.EventHandler(this.asToolStripMenuItem_Click);
            // 
            // HelpButton
            // 
            this.HelpButton.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.AboutMenu});
            this.HelpButton.Name = "HelpButton";
            this.HelpButton.Size = new System.Drawing.Size(53, 24);
            this.HelpButton.Text = "Help";
            this.HelpButton.Click += new System.EventHandler(this.HelpButton_Click);
            // 
            // AboutMenu
            // 
            this.AboutMenu.Name = "AboutMenu";
            this.AboutMenu.Size = new System.Drawing.Size(123, 24);
            this.AboutMenu.Text = "About!";
            this.AboutMenu.Click += new System.EventHandler(this.AboutMenu_Click);
            // 
            // IP_Box
            // 
            this.IP_Box.BackColor = System.Drawing.SystemColors.HighlightText;
            this.IP_Box.Location = new System.Drawing.Point(79, 144);
            this.IP_Box.Name = "IP_Box";
            this.IP_Box.Size = new System.Drawing.Size(268, 22);
            this.IP_Box.TabIndex = 3;
            this.IP_Box.Text = "Please Enter IP (IP\'s)";
            this.IP_Box.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.IP_Box.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // Port_Box
            // 
            this.Port_Box.BackColor = System.Drawing.SystemColors.HighlightText;
            this.Port_Box.Location = new System.Drawing.Point(79, 226);
            this.Port_Box.Name = "Port_Box";
            this.Port_Box.Size = new System.Drawing.Size(268, 22);
            this.Port_Box.TabIndex = 4;
            this.Port_Box.Text = "Please Enter Port Number(s)";
            this.Port_Box.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Port_Box.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(47, 506);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(425, 23);
            this.progressBar1.TabIndex = 5;
            // 
            // TCP_Button
            // 
            this.TCP_Button.AutoSize = true;
            this.TCP_Button.Location = new System.Drawing.Point(410, 145);
            this.TCP_Button.Name = "TCP_Button";
            this.TCP_Button.Size = new System.Drawing.Size(56, 21);
            this.TCP_Button.TabIndex = 6;
            this.TCP_Button.TabStop = true;
            this.TCP_Button.Text = "TCP";
            this.TCP_Button.UseVisualStyleBackColor = true;
            this.TCP_Button.CheckedChanged += new System.EventHandler(this.TCP_Button_CheckedChanged);
            // 
            // ICMP_Button
            // 
            this.ICMP_Button.AutoSize = true;
            this.ICMP_Button.Location = new System.Drawing.Point(410, 184);
            this.ICMP_Button.Name = "ICMP_Button";
            this.ICMP_Button.Size = new System.Drawing.Size(108, 21);
            this.ICMP_Button.TabIndex = 7;
            this.ICMP_Button.TabStop = true;
            this.ICMP_Button.Text = "IMCP (PING)";
            this.ICMP_Button.UseVisualStyleBackColor = true;
            this.ICMP_Button.CheckedChanged += new System.EventHandler(this.ICMP_Button_CheckedChanged);
            // 
            // UDP_Button
            // 
            this.UDP_Button.AutoSize = true;
            this.UDP_Button.Location = new System.Drawing.Point(410, 264);
            this.UDP_Button.Name = "UDP_Button";
            this.UDP_Button.Size = new System.Drawing.Size(58, 21);
            this.UDP_Button.TabIndex = 8;
            this.UDP_Button.TabStop = true;
            this.UDP_Button.Text = "UDP";
            this.UDP_Button.UseVisualStyleBackColor = true;
            this.UDP_Button.CheckedChanged += new System.EventHandler(this.UDP_Button_CheckedChanged);
            // 
            // ICMP2_Button
            // 
            this.ICMP2_Button.AutoSize = true;
            this.ICMP2_Button.Location = new System.Drawing.Point(410, 224);
            this.ICMP2_Button.Name = "ICMP2_Button";
            this.ICMP2_Button.Size = new System.Drawing.Size(179, 21);
            this.ICMP2_Button.TabIndex = 9;
            this.ICMP2_Button.TabStop = true;
            this.ICMP2_Button.Text = "FAST IMCP (ADV PING)";
            this.ICMP2_Button.UseVisualStyleBackColor = true;
            this.ICMP2_Button.CheckedChanged += new System.EventHandler(this.ICMP2_Button_CheckedChanged);
            // 
            // PingBefore
            // 
            this.PingBefore.AutoSize = true;
            this.PingBefore.Location = new System.Drawing.Point(79, 307);
            this.PingBefore.Name = "PingBefore";
            this.PingBefore.Size = new System.Drawing.Size(167, 21);
            this.PingBefore.TabIndex = 10;
            this.PingBefore.Text = "Ping Before Scanning";
            this.PingBefore.UseVisualStyleBackColor = true;
            this.PingBefore.CheckedChanged += new System.EventHandler(this.PingBefore_CheckedChanged);
            // 
            // CommonPorts
            // 
            this.CommonPorts.AutoSize = true;
            this.CommonPorts.Location = new System.Drawing.Point(79, 365);
            this.CommonPorts.Name = "CommonPorts";
            this.CommonPorts.Size = new System.Drawing.Size(221, 21);
            this.CommonPorts.TabIndex = 11;
            this.CommonPorts.Text = "Scan The Most Common Ports";
            this.CommonPorts.UseVisualStyleBackColor = true;
            this.CommonPorts.CheckedChanged += new System.EventHandler(this.CommonPorts_CheckedChanged);
            // 
            // CLR_IP_Button
            // 
            this.CLR_IP_Button.Location = new System.Drawing.Point(12, 139);
            this.CLR_IP_Button.Name = "CLR_IP_Button";
            this.CLR_IP_Button.Size = new System.Drawing.Size(52, 27);
            this.CLR_IP_Button.TabIndex = 12;
            this.CLR_IP_Button.Text = "CLR";
            this.CLR_IP_Button.UseVisualStyleBackColor = true;
            this.CLR_IP_Button.Click += new System.EventHandler(this.CLR_IP_Button_Click);
            // 
            // CLR_Port_Button
            // 
            this.CLR_Port_Button.Location = new System.Drawing.Point(12, 221);
            this.CLR_Port_Button.Name = "CLR_Port_Button";
            this.CLR_Port_Button.Size = new System.Drawing.Size(52, 27);
            this.CLR_Port_Button.TabIndex = 13;
            this.CLR_Port_Button.Text = "CLR";
            this.CLR_Port_Button.UseVisualStyleBackColor = true;
            this.CLR_Port_Button.Click += new System.EventHandler(this.CLR_Port_Button_Click);
            // 
            // Group_IP
            // 
            this.Group_IP.AutoSize = true;
            this.Group_IP.Location = new System.Drawing.Point(233, 441);
            this.Group_IP.Name = "Group_IP";
            this.Group_IP.Size = new System.Drawing.Size(42, 21);
            this.Group_IP.TabIndex = 14;
            this.Group_IP.Text = "IP";
            this.Group_IP.UseVisualStyleBackColor = true;
            this.Group_IP.CheckedChanged += new System.EventHandler(this.Group_IP_CheckedChanged);
            // 
            // Group_Port
            // 
            this.Group_Port.AutoSize = true;
            this.Group_Port.Location = new System.Drawing.Point(319, 441);
            this.Group_Port.Name = "Group_Port";
            this.Group_Port.Size = new System.Drawing.Size(56, 21);
            this.Group_Port.TabIndex = 15;
            this.Group_Port.Text = "Port";
            this.Group_Port.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(252, 421);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(85, 17);
            this.label1.TabIndex = 16;
            this.label1.Text = "Tip Grupare";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // PortScanner
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(900, 543);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Group_Port);
            this.Controls.Add(this.Group_IP);
            this.Controls.Add(this.CLR_Port_Button);
            this.Controls.Add(this.CLR_IP_Button);
            this.Controls.Add(this.CommonPorts);
            this.Controls.Add(this.PingBefore);
            this.Controls.Add(this.ICMP2_Button);
            this.Controls.Add(this.UDP_Button);
            this.Controls.Add(this.ICMP_Button);
            this.Controls.Add(this.TCP_Button);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.Port_Box);
            this.Controls.Add(this.IP_Box);
            this.Controls.Add(this.SCAN_Button);
            this.Controls.Add(this.Afisaj);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "PortScanner";
            this.Text = "J&M\'s PortScanner";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox Afisaj;
        private System.Windows.Forms.Button SCAN_Button;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem aToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem asToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem HelpButton;
        private System.Windows.Forms.ToolStripMenuItem AboutMenu;
        private System.Windows.Forms.TextBox IP_Box;
        private System.Windows.Forms.TextBox Port_Box;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.RadioButton TCP_Button;
        private System.Windows.Forms.RadioButton ICMP_Button;
        private System.Windows.Forms.RadioButton UDP_Button;
        private System.Windows.Forms.RadioButton ICMP2_Button;
        private System.Windows.Forms.CheckBox PingBefore;
        private System.Windows.Forms.CheckBox CommonPorts;
        private System.Windows.Forms.Button CLR_IP_Button;
        private System.Windows.Forms.Button CLR_Port_Button;
        private System.Windows.Forms.CheckBox Group_IP;
        private System.Windows.Forms.CheckBox Group_Port;
        private System.Windows.Forms.Label label1;
    }
}

