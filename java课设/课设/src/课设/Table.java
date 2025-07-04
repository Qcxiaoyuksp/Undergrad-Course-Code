package 课设;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JTextArea;
import java.awt.Font;
import java.awt.SystemColor;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Color;

public class Table extends JFrame {
	private JPanel contentPane;
	/**
	 *启动应用程序
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Table frame = new Table();
					frame.setVisible(true);
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
	public Table() {
		setTitle("Choice");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(750,350,450,300);//界面大小
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);//面板背景着色
		contentPane.setForeground(Color.WHITE);//面板前景着色
		contentPane.setBorder(new EmptyBorder(5,5,5,5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		/**
		 *设置界面标题
		 */
		JTextArea txtrYouWant = new JTextArea();
		txtrYouWant.setBackground(SystemColor.menu);
		txtrYouWant.setFont(new Font("宋体",Font.PLAIN,21));
		txtrYouWant.setEditable(false);
		txtrYouWant.setText("Please click your choice");
		txtrYouWant.setBounds(80,45,265,30);
		contentPane.add(txtrYouWant);
		/**
		 *设置Add按钮
		 */
		JButton btnAdd = new JButton("Add product");
		btnAdd.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				Add frame = new Add();
				frame.setVisible(true);
			}
		});
		btnAdd.setBounds(30,125,150,30);
		contentPane.add(btnAdd);
		/**
		 *设置Delete按钮
		 */
		JButton btnDelete = new JButton("Delete product");
		btnDelete.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Delete frame = new Delete();
				frame.setVisible(true);
			}
		});
		btnDelete.setBounds(250,125,150,30);
		contentPane.add(btnDelete);
		/**
		 *设置Update按钮
		 */
		JButton btnUpdate = new JButton("Update product");
		btnUpdate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Update frame = new Update();
				frame.setVisible(true);
			}
		});
		btnUpdate.setBounds(30,180,150,30);
		contentPane.add(btnUpdate);
		/**
		 *设置Find按钮
		 */
		JButton btnFind = new JButton("Find product");
		btnFind.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				Find frame = new Find();
				frame.setVisible(true);
			}
		});
		btnFind.setBounds(250,180,150,30);
		contentPane.add(btnFind);
	}
}