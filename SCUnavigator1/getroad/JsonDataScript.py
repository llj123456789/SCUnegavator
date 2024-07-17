import xml.etree.ElementTree as ET
import json

# 读取 SVG 文件
input_file = 'E:\yangyang c I\编程实战\schoolmap.svg'

# 解析 SVG 文件
tree = ET.parse(input_file)
root = tree.getroot()

# 获取命名空间
namespace = {'svg': 'http://www.w3.org/2000/svg'}

# 初始化空列表以存储信息
locations = []
vertices = []

# 提取景点（Locations）
for location in root.findall(".//svg:g[@id='Location']/svg:circle", namespace):
    loc_info = {
        "id": location.get("id"),
        "name": location.get("id"),  # 使用 id 作为 name，因为 data-name 不存在
        "style": location.get("style"),
        "cx": float(location.get("cx")),
        "cy": float(location.get("cy")),
        "r": float(location.get("r"))
    }
    locations.append(loc_info)

# 提取节点（Vertices）
for vertice in root.findall(".//svg:g[@id='Vertice']/svg:circle", namespace):
    vertice_info = {
        "id": vertice.get("id"),
        "name": vertice.get("id"),  # 使用 id 作为 name，因为 data-name 不存在
        "style": vertice.get("style"),
        "cx": float(vertice.get("cx")),
        "cy": float(vertice.get("cy")),
        "r": float(vertice.get("r"))
    }
    vertices.append(vertice_info)



# 将提取的信息分类到对应的列表

outputVertices = []
outputLocations = []

for loc in locations:
    outputLocations.append(loc)

for vert in vertices:
    outputVertices.append(vert)



# 初始化 graph 数据结构
graph = {
    "Vertices": [],
    "Locations": []
}

# 添加 Vertices
verticeCount = 0
for vertice in outputVertices:
    graph["Vertices"].append({
        "Id": verticeCount,
        "Name": vertice["name"],
        "X": vertice["cx"],
        "Y": vertice["cy"]
    })
    verticeCount += 1


# 添加 Locations
for location in outputLocations:
    graph["Locations"].append({
        "Id": verticeCount+1005,
        "Name": location["name"],
        "X": location["cx"],
        "Y": location["cy"],
    
    })
    verticeCount += 1

# 打印 graph 数据结构
print(json.dumps(graph, indent=4, ensure_ascii=False))
