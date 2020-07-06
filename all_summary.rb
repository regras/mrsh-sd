#!/usr/bin/env ruby
require "./objects.rb"

$types = ['jpg', 'pdf', 'doc', 'ppt', 'html', 'xls', 'text', 'gif']
$results = Hash.new


$sumy_p_file = Hash.new     ##summary per file


$scores = [80, 60, 40, 30, 20, 15, 10, 5, 1, 0]




def analyze(dirname, sdhashes_file)
    
    #prepare sdhash file
    sdhash_map = sdhashes_to_hashmap(sdhashes_file)
    
    #print heading
    print "entropy, SDM-file, all File, SDM-p, all packet"
    $types.each do |type|
        print ", ", type
    end
    puts

    
    #iterate through files in 'dirname'
    Dir.chdir(dirname)
    for i in 0..32 do
        e = ((0.2*i*10).to_i)/10.0
        Dir.foreach(".") do |file|
            # something mac specific
            if file.include?(e.to_s)
                find_best_sdhash_match(file, sdhash_map)
                print_them(file)
            end
        end
    end
end



def print_them(filename)

    t = filename.split("_")
    print t[2], ", "

    #    print $sumy_p_file['tp_file'].to_i, ", "
    print ($sumy_p_file['tp_file'].to_f / $sumy_p_file['all_files'].to_f).round(3), ", "
    print $sumy_p_file['all_files'].to_i, ", "
    #print "f",$sumy_p_file['tp_packets'].to_i, "f",", "
    print ($sumy_p_file['tp_packets'].to_f / $sumy_p_file['all_packets'].to_f).round(3), ", "
    print $sumy_p_file['all_packets'].to_i
    
    $types.each do |type|
       print ", ", $sumy_p_file[type].to_i
    end
    
    puts
    
end


#generates true positive statistics
def find_best_sdhash_match(mrsh_net, sdhash_map)
    
    #Reset statistics
    $sumy_p_file = Hash.new
    
    #iterate through mrsh results
    file = File.open(mrsh_net, "rb").read
    file.each_line do |line|
        p_array = line.gsub(" \n", "").split(" ")
                
        #look in sdhash file for a match
        name = get_filename(p_array[0])
        tmp = sdhash_map[name]
        type = name.split(".")[1]
        
      
      #        if type == "pdf"
      #     next
      # end

        $sumy_p_file['all_files'] = $sumy_p_file['all_files'].to_i + 1     #count all files
        $sumy_p_file['all_packets'] = $sumy_p_file['all_packets'].to_i + p_array[1].to_i
        $sumy_p_file[type] = $sumy_p_file[type].to_i + 1

        #store it to results
        if tmp != nil
            $sumy_p_file['tp_file'] = $sumy_p_file['tp_file'].to_i + 1
            $sumy_p_file['tp_packets'] = $sumy_p_file['tp_packets'].to_i+ p_array[1].to_i
            
            $scores.each do |score|
                if tmp.score > score
                    $sumy_p_file[score] = $sumy_p_file[score].to_i + 1
                    break
                end
            end
        end
        
    end
end


def sdhashes_to_hashmap(sdhashes_file)
    #reading hash comaprsion file and build a hashmap
    sdhash_map = Hash.new
    file = File.open(sdhashes_file, "rb").read
    file.each_line do |line|
        #split up the lines to get file names and scores
        lineArr = line.gsub(" \n", "").split("|")
           
        m = MATCH.new
        m.name1 = get_filename(lineArr[0])
        m.name2 = get_filename(lineArr[1])
        m.score = lineArr[2].to_i
           
        #stores best match score for files 
        if sdhash_map[m.name1] == nil || sdhash_map[m.name1].score <= m.score
            sdhash_map[m.name1] = m
        end
        if sdhash_map[m.name2] == nil || sdhash_map[m.name2].score <= m.score
           sdhash_map[m.name2] = m
        end
    end
    return sdhash_map
end


def get_filename(str)
    t = str.split("/")
    return t[t.length-1]
end


def equal_files?(file1, file2)
    f1 = file1.split(".")
    t1 = f1[f1.length - 1]
    f2 = file2.split(".")
    t2 = f2[f2.length - 1]
    return t1==t2
end


#updates counter for a 'file' based on a given package
def update_packet_counter(myfile, packet)
    myfile.total = myfile.total.to_i+1
    if(packet[4].to_i >= $MIN_RUN)
        $total_pos_p = $total_pos_p + 1
        myfile.pos = myfile.pos.to_i + 1
    end
    return myfile
end
    
def splitLine(line)
    tmp = line.gsub(" \n", "").split("/")
    return tmp[tmp.length-1].split(",")
end


analyze(ARGV[0], ARGV[1])



