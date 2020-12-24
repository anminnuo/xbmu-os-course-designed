package chat;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.*;
import java.awt.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.SimpleDateFormat;
import java.util.Date;

import chat.*;

import javax.swing.*;

public class ClientView extends JFrame implements ActionListener, KeyListener, Runnable {
    private static final MouseEvent MouseEvent = null;
	private JTextArea textArea;
    private JTextField textField, tfName;
    private JButton btnSend, btnId;
    private JLabel label;
    private JPanel jp1, jp2;
    public boolean isConnect = false;
    private Socket socket = null;
    private DataInputStream inputStream = null;
    private DataOutputStream outputStream = null;
    private JScrollPane scrollPane;
    private static ClientView view;

    public JTextArea getTextArea() {
        return textArea;
    }

    public DataInputStream getInputStream() {
        return inputStream;
    }
    public DataOutputStream getOutputStream() {
        return outputStream;
    }

    public static void main(String[] args) {
    	  Window window = new Window();
    	  window.show();
//	    	MyDBConnection myDB=new MyDBConnection();
//	    	MyDBOperation myOpr=new MyDBOperation(myDB);
//	        window.mouseClicked(MouseEvent);
//	        window.mouseEntered(MouseEvent);
//	        window.mouseExited(MouseEvent);
    	view = new ClientView();
        ServiceView.clientViews.add(view);
        Thread thread = new Thread(view);
        thread.start();
    }

    public ClientView() {
        initView();
        try {
            socket = new Socket("localhost", 9090);//���ӱ��ط�����

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void initView() {
    	int i=0,j=0;
        j=i+1;
        textArea = new JTextArea(20, 20);
        textArea.setEditable(false);
        scrollPane = new JScrollPane(textArea);
        textField = new JTextField(15);
        textField.addKeyListener(this);
        btnSend = new JButton("����");
        btnSend.addActionListener(this);
        label = new JLabel("�ǳƣ�");
        tfName = new JTextField(8);
        jp1 = new JPanel();
        jp2 = new JPanel();
        jp1.add(label);
        jp1.add(tfName);
        tfName.setText("�û�"+j);
        jp1.setLayout(new FlowLayout(FlowLayout.CENTER));
        jp2.add(textField);
        jp2.add(btnSend);
        jp2.setLayout(new FlowLayout(FlowLayout.CENTER));
   
    	

		//��ʾʱ��
		JLabel timelabel = new JLabel("AM"); 
		add(timelabel);
		timelabel.setBounds(90, 61, 280, 32);
		timelabel.setFont(new Font("����", Font.BOLD, 16));
	    timelabel.setForeground(new Color(0, 0, 0)); 
	    Timer time = new Timer(1000,new ActionListener(){
		  public void actionPerformed(ActionEvent arg0) {
		  timelabel.setText(new SimpleDateFormat("yyyy��MM��dd�� EEEE hh:mm:ss").format(new Date()));
		  } 
		  });
		time.start(); 
        
        add(jp1, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(jp2, BorderLayout.SOUTH);
        setTitle("simple chat");
        setSize(500, 500);
        setLocation(450, 150);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        addWindowListener(new WindowAdapter() { //���ڹرպ�Ͽ�����
            public void windowClosing(WindowEvent e) {
                try {
                    if (socket != null)
                        socket.close();
                    if (inputStream!= null)
                        inputStream.close();
                    if (outputStream != null)
                        outputStream.close();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == btnSend) {
            sendMsg();
        }
    }

    private void sendMsg() {
        try {
            String s = textField.getText();
            if (!s.equals("")) { //��������
                textField.setText("");
                textArea.append("��(" + tfName.getText() +  "):\r\n" + s + "\r\n");
                outputStream = new DataOutputStream(socket.getOutputStream());
                outputStream.writeUTF(tfName.getText() + "#" + s); 
                outputStream.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }



    @Override
    public void keyPressed(KeyEvent arg0) {
        if (arg0.getKeyCode() == KeyEvent.VK_ENTER) {
            sendMsg();
        }
    }

    @Override
    public void keyReleased(KeyEvent arg0) {

    }

    @Override
    public void keyTyped(KeyEvent arg0) {

    }

    @Override
    public void run() {
        try {
            inputStream = new DataInputStream(socket.getInputStream());

            while (true) {
                String[] s = inputStream.readUTF().split("#");
                textArea.append(s[0] + ":\r\n" + s[1] + "\r\n");
            }
        } catch (IOException e) {
        }

    }
}