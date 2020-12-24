package chat;
import chat.ClientMannager;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.ArrayList;
import java.net.Socket;
import chat.Service;
import javax.swing.*;

public class ServiceView extends JFrame implements ActionListener{
    private JButton btnOpen, btnStop;
    private JLabel label;
    private Service service = null;
    public static ArrayList<ClientView> clientViews = new ArrayList<>();
    private static ServiceView view;

    public static ServiceView getView() {
        return view;
    }
    public static void main(String[] args) {
        view = new ServiceView();
    }

    public ServiceView() {
        initView();
    }

    private void initView() {
        btnOpen = new JButton("�򿪷�����");
        btnStop = new JButton("�رշ�����");
        btnStop.setEnabled(false);
        btnOpen.addActionListener(this);
        btnStop.addActionListener(this);
        label = new JLabel("������ֹͣ����");
        add(label);
        add(btnOpen);
        add(btnStop);
        setTitle("������");
        setLayout(new GridLayout(3, 1, 0, 10));
        setSize(300, 300);
        setLocation(450, 150);
        setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == btnOpen) {
            open();
        } else {
            stop();
        }
    }

    public void open() { //����������
        service = new Service();
        Thread thread = new Thread(service);
        thread.start();
        label.setText("��������������");
        btnOpen.setEnabled(false);
        btnStop.setEnabled(true);
    }

    public void stop() { //�رշ�����
        label.setText("�������ѹر�");
        btnOpen.setEnabled(true);
        btnStop.setEnabled(false);
        try {
            synchronized (ClientMannager.sockets) { //�رո�������
                for (ChatSocket socket:ClientMannager.sockets) {
                   
                    socket.getOutputStream().close();
                    socket.getInputStream().close();
                }
                ClientMannager.sockets.removeAllElements();
            }


            for (ClientView view : clientViews) {
                view.getInputStream().close();
                view.getOutputStream().close();
            }

           service.getServerSocket().close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}