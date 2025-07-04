package 课设;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextArea;
import java.awt.SystemColor;
import java.awt.Font;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Choice;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.awt.Color;

public class Update extends JFrame {
	private JPanel contentPane;
	private JTextField textField;
	private JTextField textField_1;
	/**
	 *启动应用程序
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Update frame = new Update();
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
	public Update() {
		setTitle("Update");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(750,350,450,300);//界面大小
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);//面板背景着色
		contentPane.setBorder(new EmptyBorder(5,5,5,5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		/**
		 *界面布局
		 */
		JTextArea txtrInput = new JTextArea();
		txtrInput.setFont(new Font("宋体",Font.PLAIN,16));
		txtrInput.setBackground(SystemColor.menu);
		txtrInput.setEditable(false);
		txtrInput.setText("Please input the productName you want to update\uFF1A");
		txtrInput.setBounds(20,30,385,20);
		contentPane.add(txtrInput);
		textField = new JTextField();
		textField.setFont(new Font("宋体",Font.PLAIN,16));
		textField.setBounds(20,70,385,25);
		contentPane.add(textField);
		textField.setColumns(10);
		JTextArea txtrYouWant = new JTextArea();
		txtrYouWant.setBackground(SystemColor.menu);
		txtrYouWant.setEditable(false);
		txtrYouWant.setFont(new Font("宋体",Font.PLAIN,16));
		txtrYouWant.setText("What do you want to update\uFF1A");
		txtrYouWant.setBounds(20,125,215,20);
		contentPane.add(txtrYouWant);
		Choice choice = new Choice();
		choice.add("productID");
		choice.add("productAveragePrice");
		choice.add("productScore");
		choice.setFont(new Font("宋体",Font.PLAIN,16));
		choice.setBounds(255,125,150,25);
		contentPane.add(choice);
		textField_1 = new JTextField();
		textField_1.setFont(new Font("宋体",Font.PLAIN,16));
		textField_1.setBounds(20,165,385,25);
		contentPane.add(textField_1);
		textField_1.setColumns(10);
		/**
		 *设置确认按钮
		 */
		JButton btnConfirm = new JButton("Confirm");
		btnConfirm.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Connection con;
		        Statement stat; 
		        ResultSet rs;
		        try {  
		        	 Class.forName("org.sqlite.JDBC");//加载驱动类 
		        }
		        catch(Exception e1){
		        	java.lang.System.out.println(""+e1);
		        }
		        try{   
		        	con=DriverManager.getConnection("jdbc:sqlite://d:/javakeshe/digital products.s3db");//创建数据库连接
		            stat=con.createStatement();
		            //将输入信息在数据库中找到并删除
		            String s=new String("update digitalProducts set "+choice.getSelectedItem()+"='"+textField_1.getText()+"' where productName='"+textField.getText()+"'");
		            java.lang.System.out.println(s);
		            int count=stat.executeUpdate(s);
		            if(count==1)
		            	java.lang.System.out.println("Update succeeded!");
		            else
		            	java.lang.System.out.println("Update false!");
		            rs=stat.executeQuery("select * from digitalProducts");//查询数据库中的信息
		            //打印数据库中信息
		            while(rs.next()){
		            	int productID=rs.getInt(1);
		                String productName=rs.getString(2);
		                float productAveragePrice=rs.getFloat(3);
		                float productScore=rs.getFloat(4);
		                java.lang.System.out.println(productID+","+productName+","+productAveragePrice+","+productScore);
		            }
		            con.close();
		        }
		        catch(SQLException e1){
		        	java.lang.System.out.println(e1);
		        }
			}
		});
		btnConfirm.setBounds(140,205,150,30);
		contentPane.add(btnConfirm);
	}
}