import tkinter as tk
import random
import string

def start_chaos():
    # 创建主窗口
    root = tk.Tk()
    root.title("桌面乱码跳动")
    
    # 获取屏幕宽度和高度
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    
    # 设置窗口全屏、置顶、无边框、半透明
    root.geometry(f"{screen_width}x{screen_height}+0+0")
    root.attributes('-topmost', True)      # 始终在最上层
    root.attributes('-alpha', 0.8)         # 透明度 (0.0 - 1.0)
    root.overrideredirect(True)            # 去除标题栏和边框
    root.configure(bg='black')             # 背景色

    # 创建画布
    canvas = tk.Canvas(root, bg='black', highlightthickness=0)
    canvas.pack(fill=tk.BOTH, expand=True)

    # 定义字符集 (你可以改成中文或其他符号)
    chars = string.ascii_letters + string.digits + "~!@#$%^&*()_+-=[]{}|;:,.<>?"

    # 存储乱码对象列表: (文本ID, x坐标, y坐标, x速度, y速度)
    items = []
    num_items = 150  # 乱码的数量，可以根据电脑性能调整

    # 初始化乱码
    for _ in range(num_items):
        x = random.randint(0, screen_width)
        y = random.randint(0, screen_height)
        char = random.choice(chars)
        # 随机颜色 (霓虹色系)
        color = f"#{random.randint(100, 255):02x}{random.randint(0, 150):02x}{random.randint(100, 255):02x}"
        font_size = random.randint(10, 20)
        
        text_id = canvas.create_text(x, y, text=char, fill=color, font=("Consolas", font_size, "bold"))
        # 随机速度 (-3 到 3)
        vx = random.randint(-3, 3)
        vy = random.randint(-3, 3)
        
        items.append([text_id, x, y, vx, vy])

    # 动画循环函数
    def animate():
        for item in items:
            text_id, x, y, vx, vy = item
            
            # 更新位置
            x += vx
            y += vy
            
            # 边界反弹逻辑
            if x <= 0 or x >= screen_width:
                vx = -vx
                item[3] = vx # 更新速度
            if y <= 0 or y >= screen_height:
                vy = -vy
                item[4] = vy # 更新速度
            
            # 移动画布上的文字
            canvas.move(text_id, vx, vy)
            
            # 偶尔改变字符内容，增加“乱码”感 (5%的概率)
            if random.random() < 0.05:
                canvas.itemconfig(text_id, text=random.choice(chars))

        # 每 30 毫秒刷新一次 (约33帧/秒)
        root.after(30, animate)

    # 启动动画
    animate()
    
    # 点击鼠标退出
    def close_app(event=None):
        root.destroy()
    
    root.bind("<Button-1>", close_app) # 左键点击关闭
    root.bind("<Escape>", close_app)   # 按ESC关闭

    root.mainloop()

if __name__ == "__main__":
    start_chaos()