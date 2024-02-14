import pandas as pd

banks = pd.read_csv("bank.csv")
countries = pd.read_csv("country.csv")

with open("create_banks", "w+") as f:
    print(
        'schema.vertexLabel("Bank").properties().String().String().Int64().Double().Double().String().create()',
        file=f,
    )
    for index, row in banks.iterrows():
        print(
            f'g.addVertex("Bank", "{row["n.country"]}", "{row["n.id"]}", {row["n.srid"]}, {row[" n.x"]}, {row[" n.y"]}, {row["n.name"]})',
            file=f,
        )

# with open("create_countries", "w+") as f:
#     for index, row in countries.iterrows():
#         print(
#             f'g.addVertex("Country", "{row["n.code"]}", {row["n.srid"]}, {row["n.x"]}, {row["n.y"]}, "{row["n.name"]}", "{row["n.tld"]}")'.encode(
#                 "utf-8"
#             ),
#             file=f,
#         )

with open("create_edges", "w+") as f:
    print('schema.edgeLabel("Country").create()', file=f)
    for index, row in countries.iterrows():
        print(
            f'g.addEdge("Country", V().hasLabel("Bank").has(0, "{row["n.code"]}"), V().hasLabel("Country").has(0, "{row["n.code"]}"))',
            file=f,
        )
