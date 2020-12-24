package chat;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import chat.*;
import javax.swing.JOptionPane;

/*�������ˣ�ʹ���̴߳ﵽѭ���ȴ����ӵ�Ŀ��*/
public class Service implements Runnable{

    private ServerSocket serverSocket = null;

    public ServerSocket getServerSocket() {
        return serverSocket;
    }

    @Override
    public void run() {
        try {
            serverSocket = new ServerSocket(9090); //�����˿�
            while (true) { //ѭ�ؽ��տͻ��˵�����
                Socket socket = serverSocket.accept();
                JOptionPane.showMessageDialog(ServiceView.getView(), "�ͻ������Ӷ˿�", "TIP", JOptionPane.INFORMATION_MESSAGE);
                ChatSocket chatSocket = new ChatSocket(socket); //�¿ͻ�������
                ClientMannager.sockets.add(chatSocket); //���ͻ��˹���������ӿͻ�
                Thread thread = new Thread(chatSocket); //�����߳�ʹ��������ʼ���Ͻ��տͻ�����Ϣ
                thread.start();

            }
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("�������ر�");
        }
    }

}