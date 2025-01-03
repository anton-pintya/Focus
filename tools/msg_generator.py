import jinja2
import os


def main():
    env = jinja2.Environment(loader=jinja2.FileSystemLoader(searchpath=os.getcwd()))

    template = env.get_template(f"./tools/msg_template_hpp.j2")

    for file in os.listdir(f"{os.getcwd()}/core/transport/msg"):
        with open(f"{os.getcwd()}/core/transport/msg/{file}", "r+") as f:
            topic_file = f.read()
            topic_name = f.name.split("/")[-1].split(".")[0]
            lines = topic_file.split('\n')

        for line in lines:
            if line == "":
                lines.remove(line)
                continue

            if line[-1] == '\n':
                line = line[:-2]

        result = template.render(filename=topic_name + ".hpp", topic_name=topic_name, lines=lines)

        if (os.path.isdir(f"{os.getcwd()}/core/transport/msg_generated") == False):
            os.mkdir(f"{os.getcwd()}/core/transport/msg_generated")

        with open(f"{os.getcwd()}/core/transport/msg_generated/{topic_name}.hpp", "w+") as f:
            f.write(result)

if __name__ == "__main__":
    main()