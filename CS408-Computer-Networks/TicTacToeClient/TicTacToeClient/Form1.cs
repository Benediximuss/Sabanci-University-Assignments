using Microsoft.VisualBasic.Logging;
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Text;
using System.Text.Json.Serialization;
using System.Windows.Forms;
using System.Xml.Linq;
using static System.Windows.Forms.AxHost;

namespace TicTacToeClient
{
    public partial class Form1 : Form
    {
        // Form Components
        List<List<Button>> buttonsMatrix = new List<List<Button>>();

        // Game information
        string username;
        List<string> usernames = new List<string>();

        // Game logic
        bool isJoined = false;
        bool isYourTurn = false;
        char side;

        // Network components comoon
        Socket clientSocket;

        // Style components

        // Constructor
        public Form1()
        {
            /*To access UI elements in multi-thread level*/
            Control.CheckForIllegalCrossThreadCalls = false;

            InitializeComponent();

            // Other initializations
            setInfoText("init");
            initButtonsMatrix();
            DisableBlueHighlight();


            textBox_IP.Text = "192.168.1.22"; // sevval 
            textBox_Port.Text = "3131";

            textBox_Name.Text = "ugurpasa";
        }


        // Buttons
        private void btn_Connect_Click(object sender, EventArgs e)
        {

            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            int port;
            if (Int32.TryParse(textBox_Port.Text, out port)) // Checks port's validity
            {
                try
                {
                    clientSocket.Connect(textBox_IP.Text, port); // Tries to connect, if cannot throw exception

                    toggleComponentsEnabled(false, label_IP, label_Port, textBox_IP, textBox_Port, btn_Connect);
                    setInfoText("connected");

                    Thread recieveThread = new Thread(serverListener); // Start Recieve function to recieve message from server
                    recieveThread.Start();
                }
                catch (Exception exc)
                {
                    AppendColoredText("Couldn't connect to the server!\n", colors["Warnings"]);
                    //richTextBox_Log.AppendText("Couldn't connect to the server!\n");
                }
            }
            else
            {
                AppendColoredText("Invalid port number, try again!\n", colors["Warnings"]);
                //richTextBox_Log.AppendText("Invalid port number, try again!\n");
            }

        }

        private void btn_Join_Click(object sender, EventArgs e)
        {
            username = textBox_Name.Text;

            if (string.IsNullOrWhiteSpace(username))
            {
                AppendColoredText("Invalid username!\n", colors["Warnings"]);
                textBox_Name.Clear();
            }
            else
            {
                Byte[] buffer_send = Encoding.Default.GetBytes("join:" + username);
                try
                {
                    clientSocket.Send(buffer_send); // Sending username for server to be checked

                    toggleComponentsEnabled(false, label_Name, textBox_Name, btn_Join, btn_Disconnect);

                    setInfoText("waiting");
                }
                catch
                {
                    AppendColoredText("Couldn't send message to the server, try again!\n", colors["Warnings"]);
                }
            }
        }

        private void btn_Disconnect_Click(object sender, EventArgs e)
        {
            if (isJoined) // leave room
            {
                leaveRoom();
                toggleComponentsEnabled(true, btn_Join, textBox_Name, btn_Disconnect);
                toggleComponentsEnabled(false, btn_Queue, btn_Accept);
                btn_Disconnect.Text = "Disconnect";
                isJoined = false;
            }
            else // disconnect server
            {
                toggleComponentsEnabled(true, label_IP, label_Port, textBox_IP, textBox_Port, btn_Connect);
                toggleComponentsEnabled(false, textBox_Name, btn_Join, btn_Disconnect);

                textBox_Name.Clear();

                clientSocket.Close();
                clientSocket.Dispose();

            }
        }

        private void btn_Queue_Click(object sender, EventArgs e)
        {
            string msg = $"queue:{username}";
            Byte[] buffer_send = Encoding.Default.GetBytes(msg);

            try
            {
                clientSocket.Send(buffer_send);
                toggleComponentsEnabled(false, btn_Queue);
                setInfoText("inqueue");
                //clearAllButtons();
            }
            catch
            {
                AppendColoredText("Couldn't send queue request, try again!\n", colors["Warnings"]);
            }
        }

        private void btn_Accept_Click(object sender, EventArgs e)
        {
            string msg = $"accept:{username}:{side}";
            Byte[] buffer_send = Encoding.Default.GetBytes(msg);

            try
            {
                clientSocket.Send(buffer_send);
                AppendColoredText("You've accept the game!\n", colors["Status"]);
                //richTextBox_Log.AppendText("You've accept the game!\n");
                toggleComponentsEnabled(false, btn_Accept);
                setInfoText("accepted");
            }
            catch
            {
                AppendColoredText("Couldn't accept, try again!\n", colors["Warnings"]);
                //richTextBox_Log.AppendText("Couldn't accept, try again!\n");
            }
        }

        private void btn_clearLog_Click(object sender, EventArgs e)
        {
            richTextBox_Log.Clear();
        }

        // Connection
        private void leaveRoom()
        {
            string msg = $"leave:{username}";
            Byte[] buffer_send = Encoding.Default.GetBytes(msg);

            try
            {
                clientSocket.Send(buffer_send);
                AppendColoredText("You've left the room!\n", colors["Status"]);
                //richTextBox_Log.AppendText("You've left the room!\n");
                username = string.Empty;
                side = '\0';
                clearAllButtons();
                toggleButtonsEnabled(false);
                setVersusLabels(" ", " ");
                setInfoText("connected");
                richTextBox_Leaderboard.Clear();
            }
            catch
            {
                AppendColoredText("Couldn't leave, try again!\n", colors["Warnings"]);
                //richTextBox_Log.AppendText("Couldn't leave, try again!\n");
            }
        }

        private void serverListener()
        {
            while (clientSocket.Connected)
            {
                try
                {
                    string[] token = receiveResponse();

                    if (token[0] == "200") // Connected successfully
                    {
                        AppendColoredText("You have successfully connected to the server!\n", colors["Status"]);

                        toggleComponentsEnabled(true, label_Name, textBox_Name, btn_Join, btn_Disconnect);
                    }
                    else if (token[0] == "400") // Server full
                    {
                        AppendColoredText("Couldn't connect to the server, it is full now!\n", colors["Warnings"]);

                        toggleComponentsEnabled(true, label_IP, label_Port, textBox_IP, textBox_Port, btn_Connect);

                        clientSocket.Close();
                    }

                    else if (token[0] == "201") // Username approved, joined successfully
                    {
                        isJoined = true;
                        AppendColoredText(token[1], colors["Status"]);

                        Thread tgllethread = new Thread(() => toggleComponentsEnabledDelay(400, true, btn_Queue, btn_Disconnect));
                        tgllethread.Start();
                        
                        setInfoText("joined");
                        btn_Disconnect.Text = "Leave";
                    }
                    else if (token[0] == "401") // Invalid username
                    {
                        AppendColoredText(token[1], colors["Warnings"]);

                        toggleComponentsEnabled(true, label_Name, textBox_Name, btn_Join, btn_Disconnect);
                        setInfoText("connected");
                        username = "";
                    }

                    else if (token[0] == "startreq")
                    {
                        AppendColoredText(token[2], colors["Prompts"]);
                        toggleComponentsEnabled(true, btn_Accept);
                        setInfoText("gamefound", token[1]);
                        side = token[1][0];
                    }
                    else if (token[0] == "startplay")
                    {
                        toggleComponentsEnabled(false, btn_Accept);
                        clearAllButtons();
                        setInfoText("gamestarts", side.ToString());
                        setInfoText("nturn");
                    }
                    else if (token[0] == "yourturn")
                    {
                        isYourTurn = side.ToString() == token[1] ? true : false;

                        if (isYourTurn)
                        {
                            updateUnplayedButtons();
                            setInfoText("turn", token[1]);
                        }
                    }

                    else if (token[0] == "update")
                    {
                        if (token[1] == "newplayer")
                        {
                            if (token[2] != username)
                                usernames.Add(token[2]);
                            richTextBox_Log.AppendText($"{token[2]} has joined the game room!\n");
                        }
                        else if (token[1] == "currentplayers")
                        {
                            string[] nameslist = token[2].Trim('\0').Split(',');

                            foreach (string name in nameslist)
                            {
                                if (!usernames.Contains(name) && name != username)
                                {
                                    usernames.Add(name);
                                    richTextBox_Log.AppendText(name);
                                    richTextBox_Log.AppendText(" is in the room\n");
                                }
                            }

                        }
                        else if (token[1] == "left")
                        {
                            if (token[2] == "X")
                                setVersusLabels("", label_currentPlayer2.Text);
                            else if (token[2] == "O")
                                setVersusLabels(label_currentPlayer2.Text, "");

                            richTextBox_Log.AppendText(token[3]);
                        }
                        else if (token[1] == "leaderboard")
                        {
                            richTextBox_Leaderboard.Clear();
                            richTextBox_Leaderboard.AppendText(token[2]);
                        }
                        else if (token[1] == "vs")
                        {
                            toggleComponentsEnabled(true, label_currentPlayer1, label_currentPlayer2, label_CurrentGame);
                            setVersusLabels(token[2], token[3]);
                        }
                        else if (token[1] == "board")
                        {
                            updateGameBoard(token[2]);
                            highlightWin();
                        }
                        else if (token[1] == "label")
                        {
                            setVersusLabels(token[2], token[3]);
                        }
                        else if (token[1] == "finish")
                        {
                            toggleButtonsEnabled(false);
                            toggleComponentsEnabled(true, btn_Queue);
                            isYourTurn = false;


                            if (token[2] == "draw")
                            {
                                setInfoText("draw");
                            }
                            else
                            {
                                setInfoText("win/loss", token[2]);
                            }
                        }
                    }

                    else if (token[0] == "info")
                    {
                        richTextBox_Log.AppendText(token[1]);
                    }
                }
                catch (Exception exc)
                {
                    AppendColoredText(exc.Message + '\n', colors["Warnings"]);
                    AppendColoredText("Lost connection with the server!\n", colors["Warnings"]);
                    resetAll();
                }
            }
        }

        private string[] receiveResponse()
        {
            Byte[] buffer = new Byte[512];
            clientSocket.Receive(buffer);
            string response = Encoding.Default.GetString(buffer);

            string[] token = response.Trim('\0').Split(':');
            return token;
        }

        // Game functions
        private void makeMove(Button clickedButton)
        {
            string coords = clickedButton.Name.Split('_')[1];
            string msg = $"move:{coords[0]}-{coords[1]}";
            Byte[] buffer_send = Encoding.Default.GetBytes(msg);

            try
            {
                isYourTurn = false;
                updateUnplayedButtons();
                setInfoText("nturn");
                clientSocket.Send(buffer_send);
            }
            catch
            {
                AppendColoredText("Couldn't play, try again!\n", colors["Warnings"]);
                //richTextBox_Log.AppendText("Couldn't play, try again!\n");
            }

        }

        private void updateGameBoard(string boardSerial)
        {
            string[] boardsplt = boardSerial.Split(',');

            buttonsMatrix[0][0].Text = boardsplt[0];
            buttonsMatrix[0][1].Text = boardsplt[1];
            buttonsMatrix[0][2].Text = boardsplt[2];
            buttonsMatrix[1][0].Text = boardsplt[3];
            buttonsMatrix[1][1].Text = boardsplt[4];
            buttonsMatrix[1][2].Text = boardsplt[5];
            buttonsMatrix[2][0].Text = boardsplt[6];
            buttonsMatrix[2][1].Text = boardsplt[7];
            buttonsMatrix[2][2].Text = boardsplt[8];
           
        }

        private void updateUnplayedButtons()
        {
            foreach (List<Button> row in buttonsMatrix)
            {
                foreach (Button button in row)
                {
                    button.Enabled = (isYourTurn && button.Text == " ") ? true : false;
                }
            }
        }


        // Component Functions 

        void toggleComponentsEnabledDelay(int delay, bool state, params Control[] components)
        {
            Thread.Sleep(delay);
            foreach (Control component in components)
            {
                component.Enabled = state;
            }
        }
        void toggleComponentsEnabled(bool state, params Control[] components)
        {
            foreach (Control component in components)
            {
                component.Enabled = state;
            }
        }

        private void toggleButtonsEnabled(bool state)
        {
            foreach (List<Button> row in buttonsMatrix)
            {
                foreach (Button button in row)
                {
                    button.Enabled = state;
                }
            }
        }

        private void clearAllButtons()
        {
            foreach (List<Button> row in buttonsMatrix)
            {
                foreach (Button button in row)
                {
                    button.Text = " ";
                    button.BackColor = SystemColors.ScrollBar;
                }
            }
        }

        private void setInfoText(params string[] components)
        {
            if (components[0] == "init")
                label_Notification.Text = "Enter an IP address and a Port Number to connect a server!";
            else if (components[0] == "connected")
                label_Notification.Text = "Enter a username to join the game room!";
            else if (components[0] == "joined")
                label_Notification.Text = "Join the game queue to play a game!";
            else if (components[0] == "waiting")
                label_Notification.Text = "Waiting for response...";
            else if (components[0] == "inqueue")
                label_Notification.Text = "You are in the game queue";
            else if (components[0] == "gamefound")
                label_Notification.Text = $"Found game!\nAccept for start playing as {components[1]}!";
            else if (components[0] == "accepted")
                label_Notification.Text = $"Wait for your opponent to accept!";
            else if (components[0] == "gamestarts")
                label_Notification.Text = $"You are playing as {components[1]}!";
            else if (components[0] == "turn")
                label_Notification.Text = $"{components[1]} plays\nYour turn!";
            else if (components[0] == "nturn")
                label_Notification.Text = $"{(side.ToString() == "X" ? "O" : "X")} plays\nWait...";
            else if (components[0] == "win/loss")
                label_Notification.Text = $"You {components[1]}!";
            else if (components[0] == "draw")
                label_Notification.Text = "Draw!";


        }

        private void setVersusLabels(string p1, string p2)
        {
            label_currentPlayer1.Text = p1;
            label_currentPlayer2.Text = p2;
        }

        private void resetAll()
        {
            toggleComponentsEnabled(true, label_IP, label_Port, textBox_IP, textBox_Port, btn_Connect);
            toggleComponentsEnabled(false, label_Name, textBox_Name, btn_Join, btn_Disconnect, btn_Queue, btn_Accept);
            toggleButtonsEnabled(false);
            clearAllButtons();
            setInfoText("init");
            isJoined = false;
            username = "";
        }

        // Initialization
        private void initButtonsMatrix()
        {
            List<Button> row;

            row = new List<Button>();
            row.Add(btn_00);
            row.Add(btn_01);
            row.Add(btn_02);
            buttonsMatrix.Add(row);

            row = new List<Button>();
            row.Add(btn_10);
            row.Add(btn_11);
            row.Add(btn_12);
            buttonsMatrix.Add(row);

            row = new List<Button>();
            row.Add(btn_20);
            row.Add(btn_21);
            row.Add(btn_22);
            buttonsMatrix.Add(row);
        }

        private void DisableBlueHighlight()
        {
            // Disables the blue focus highlight surrounding the buttons, for all buttons
            foreach (Button button in this.Controls.OfType<Button>())
            {
                button.TabStop = false;
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (clientSocket != null && clientSocket.Connected)
            {
                clientSocket.Close();
                clientSocket.Dispose();
            }

            Environment.Exit(0);
        }


        private void gameButtonClicked(object sender, EventArgs e)
        {
            makeMove((Button)sender);
        }

        // STYLE

        Dictionary<String, Color> colors = new Dictionary<string, Color>
        {
            { "Warnings", Color.Red },
            { "Status", Color.Gray },
            { "Prompts", Color.Maroon },
            { "Player", Color.DarkGreen },
            { "OtherPlayers", Color.Blue },
        };

        private void AppendColoredText(string text, Color color)
        {
            richTextBox_Log.SelectionStart = richTextBox_Log.TextLength;
            richTextBox_Log.SelectionLength = 0;
            richTextBox_Log.SelectionColor = color;
            richTextBox_Log.AppendText(text);
            richTextBox_Log.SelectionColor = richTextBox_Log.ForeColor; // Reset to default color
        }
        // Highlight usernames
        private void HighlightWordInRichTextBox(string word, Color color)
        {
            int startIndex = 0;
            while (startIndex < richTextBox_Log.TextLength)
            {
                int wordStartIndex = richTextBox_Log.Find(word, startIndex, RichTextBoxFinds.None);
                if (wordStartIndex == -1)
                    break;

                richTextBox_Log.SelectionStart = wordStartIndex;
                richTextBox_Log.SelectionLength = word.Length;
                richTextBox_Log.SelectionColor = color;

                startIndex = wordStartIndex + word.Length;
            }
            richTextBox_Log.SelectionStart = richTextBox_Log.TextLength;
            richTextBox_Log.SelectionLength = 0;
        }

        private void highlightUsernames()
        {
            if (isJoined)
            {
                HighlightWordInRichTextBox(username, colors["Player"]);

                foreach (string name in usernames)
                {
                    HighlightWordInRichTextBox(name, colors["OtherPlayers"]);
                }
            }

            // Promptlar marron olsun
        }

        private void richTextBox_Log_TextChanged(object sender, EventArgs e)
        {
            highlightUsernames();
        }

        private void highlightWin()
        {

            for (int i = 0; i < 3; i++)
            {
                if (buttonsMatrix[i][0].Text != " " && buttonsMatrix[i][0].Text == buttonsMatrix[i][1].Text && buttonsMatrix[i][0].Text == buttonsMatrix[i][2].Text)
                {
                    buttonsMatrix[i][0].BackColor = Color.Pink;
                    buttonsMatrix[i][1].BackColor = Color.Pink;
                    buttonsMatrix[i][2].BackColor = Color.Pink;
                }

                if (buttonsMatrix[0][i].Text != " " && buttonsMatrix[0][i].Text == buttonsMatrix[1][i].Text && buttonsMatrix[0][i].Text == buttonsMatrix[2][i].Text)
                {
                    buttonsMatrix[0][i].BackColor = Color.Pink;
                    buttonsMatrix[1][i].BackColor = Color.Pink;
                    buttonsMatrix[2][i].BackColor = Color.Pink;
                }
            }

            // Check diagonals
            if (buttonsMatrix[0][0].Text != " " && buttonsMatrix[0][0].Text == buttonsMatrix[1][1].Text && buttonsMatrix[0][0].Text == buttonsMatrix[2][2].Text)
            {
                buttonsMatrix[0][0].BackColor = Color.Pink;
                buttonsMatrix[1][1].BackColor = Color.Pink;
                buttonsMatrix[2][2].BackColor = Color.Pink;
            }

            if (buttonsMatrix[0][2].Text != " " && buttonsMatrix[0][2].Text == buttonsMatrix[1][1].Text && buttonsMatrix[0][2].Text == buttonsMatrix[2][0].Text)
            {
                buttonsMatrix[0][2].BackColor = Color.Pink;
                buttonsMatrix[1][1].BackColor = Color.Pink;
                buttonsMatrix[2][0].BackColor = Color.Pink;
            }

        }

        // Preview Move
        private void previewMove(Button clickedButton, bool isEnter)
        {
            if (isEnter)
            {
                clickedButton.Text = side.ToString();
                clickedButton.ForeColor = Color.Crimson;
            }
            else
            {
                if (isYourTurn)
                    clickedButton.Text = " ";
                clickedButton.ForeColor = SystemColors.ControlText;
            }
        }

        private void btn_MouseEnter(object sender, EventArgs e)
        {
            previewMove((Button)sender, true);
        }

        private void btn_MouseLeave(object sender, EventArgs e)
        {
            previewMove((Button)sender, false);
        }

        private void toggleButtonColor(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            if (btn.Enabled)
                btn.BackColor = SystemColors.Control;
            else
                btn.BackColor = SystemColors.ScrollBar;
        }

    }
}