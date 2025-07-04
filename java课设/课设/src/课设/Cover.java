package 课设;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextArea;
import java.awt.Font;
import java.awt.Color;
import java.awt.SystemColor;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JTextField;

public class Cover extends JFrame {	//继承JFrame类
	private JPanel contentPane;
	private JTextField txtBeta;
	/**
	 *启动应用程序
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Cover frame = new Cover();
					frame.setVisible(true);//显示窗口
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	/**
	 *建立框架
	 */
	public Cover() {
		setTitle("Digital products");//标题
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(750,350,450,300);//界面大小
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);//面板背景着色
		contentPane.setBorder(new EmptyBorder(5,5,5,5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		/**
		 *设置界面标题
		 */
		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);
		textArea.setBackground(SystemColor.menu);
		textArea.setFont(new Font("宋体",Font.PLAIN,21));
		textArea.setText("Digital products information system");
		textArea.setBounds(22,45,385,30);
		contentPane.add(textArea);
		/**
		 *设置Exit按钮
		 */
		JButton btnExit = new JButton("Exit");
		btnExit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0){
				java.lang.System.exit(0);
			}
		});
		btnExit.setBounds(260,150,110,30);
		contentPane.add(btnExit);
		/**
		 *设置Enter按钮
		 */
		JButton btnEnter = new JButton("Enter");
		btnEnter.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0){
				Table frame = new Table();
				frame.setVisible(true);
			}
		});
		btnEnter.setBounds(60,150,110,30);
		contentPane.add(btnEnter);
	}
}